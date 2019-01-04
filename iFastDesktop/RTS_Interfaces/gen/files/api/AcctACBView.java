
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account ACB summary view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctACB.doc">AcctACB.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctACBView extends IFastView implements Serializable
{

   /**
    * System Currency Name member variable.
    */
   private String _CurrencyName = null;
   
   /**
    * ACB Plug Amount member variable.
    */
   private String _ACBPlugAmt = null;
   
   /**
    * ACB Plug Date member variable.
    */
   private Date _ACBPlugDate = null;
   
   private int _RepeatCount = 0;
   
   /**
    * FundCode member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * ClassCode member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * Trade Date member array.
    */
   private Date[] _TradeDate = null;
   
   /**
    * TransAmount member array.
    */
   private String[] _TransAmount = null;
   
   /**
    * Units member array.
    */
   private String[] _Units = null;
   
   /**
    * UnitsHeld member array.
    */
   private String[] _UnitsHeld = null;
   
   /**
    * AdjustedCost member array.
    */
   private String[] _AdjustedCost = null;
   
   /**
    * ACBPerUnit member array.
    */
   private String[] _ACBPerUnit = null;
   
   /**
    * GainOrLossAmt member array.
    */
   private String[] _GainOrLossAmt = null;
   
   /**
    * Trans type description member array.
    */
   private String[] _TransTypeDesc = null;
   
   /**
    * Trans Type member array.
    */
   private String[] _TransType = null;
   
   /**
    * Historical Unit ACB member array.
    */
   private String[] _HistUnitACB = null;
   
   /**
    * ACB offset value member array.
    */
   private String[] _ACBOffset = null;
   
   /**
    * ACB Transaction Id member array.
    */
   private String[] _ACBTransId = null;
   
   /**
    * Taxable Amount member array.
    */
   private String[] _TaxableAmount = null;
   
   /**
    * Opening Market Value member array.
    */
   private String[] _OpeningMV = null;
   
   /**
    * GainOrLossCurrency member array.
    */
   private String[] _GainOrLossCurrency = null;
   

   /**
    * Constructs the AcctACBView object.
    * 
    */
   public AcctACBView()
   {
      super ( new AcctACBRequest() );
   }

   /**
    * Constructs the AcctACBView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctACBView( String hostEncoding )
   {
      super ( new AcctACBRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctACBRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctACBRequest object.
    */
   public final AcctACBRequest getRequest()
   {
      return (AcctACBRequest)getIFastRequest();
   }
        
   /**
    * Gets the System Currency Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the System Currency Name or null.
    */
   public final String getCurrencyName()
   {
      return _CurrencyName;
   }
	
   /**
    * Gets the System Currency Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the System Currency Name or the specified default value.
    */
   public final String getCurrencyName( String defaultValue )
   {
      return _CurrencyName == null ? defaultValue : _CurrencyName;
   }
                  
   /**
    * Gets the ACB Plug Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ACB Plug Amount or null.
    */
   public final String getACBPlugAmt()
   {
      return _ACBPlugAmt;
   }
	
   /**
    * Gets the ACB Plug Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ACB Plug Amount or the specified default value.
    */
   public final String getACBPlugAmt( String defaultValue )
   {
      return _ACBPlugAmt == null ? defaultValue : _ACBPlugAmt;
   }
                  
   /**
    * Gets the ACB Plug Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ACB Plug Date or null.
    */
   public final Date getACBPlugDate()
   {
      return _ACBPlugDate;
   }
	
   /**
    * Gets the ACB Plug Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ACB Plug Date or the specified default value.
    */
   public final Date getACBPlugDate( Date defaultValue )
   {
      return _ACBPlugDate == null ? defaultValue : _ACBPlugDate;
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
    * Gets the FundCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundCode or null.
    */
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the FundCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundCode or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of FundCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundCode values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the ClassCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ClassCode or null.
    */
   public final String getrxClassCode( int index )
   {
      return _rxClassCode[index];
   }
    
   /**
    * Gets the ClassCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ClassCode or the specified default value.
    */
   public final String getrxClassCode( int index, String defaultValue )
   {
      return _rxClassCode[index] == null ? defaultValue : _rxClassCode[index];
   }
    
   /**
    * Gets the array of ClassCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ClassCode values.
    */
   public final String[] getrxClassCodeArray()
   {
      return _rxClassCode;
   }
    
   /**
    * Gets the Trade Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade Date or null.
    */
   public final Date getTradeDate( int index )
   {
      return _TradeDate[index];
   }
    
   /**
    * Gets the Trade Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Date or the specified default value.
    */
   public final Date getTradeDate( int index, Date defaultValue )
   {
      return _TradeDate[index] == null ? defaultValue : _TradeDate[index];
   }
    
   /**
    * Gets the array of Trade Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade Date values.
    */
   public final Date[] getTradeDateArray()
   {
      return _TradeDate;
   }
    
   /**
    * Gets the TransAmount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransAmount or null.
    */
   public final String getTransAmount( int index )
   {
      return _TransAmount[index];
   }
    
   /**
    * Gets the TransAmount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransAmount or the specified default value.
    */
   public final String getTransAmount( int index, String defaultValue )
   {
      return _TransAmount[index] == null ? defaultValue : _TransAmount[index];
   }
    
   /**
    * Gets the array of TransAmount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransAmount values.
    */
   public final String[] getTransAmountArray()
   {
      return _TransAmount;
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
    * Gets the UnitsHeld field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UnitsHeld or null.
    */
   public final String getUnitsHeld( int index )
   {
      return _UnitsHeld[index];
   }
    
   /**
    * Gets the UnitsHeld field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UnitsHeld or the specified default value.
    */
   public final String getUnitsHeld( int index, String defaultValue )
   {
      return _UnitsHeld[index] == null ? defaultValue : _UnitsHeld[index];
   }
    
   /**
    * Gets the array of UnitsHeld fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UnitsHeld values.
    */
   public final String[] getUnitsHeldArray()
   {
      return _UnitsHeld;
   }
    
   /**
    * Gets the AdjustedCost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AdjustedCost or null.
    */
   public final String getAdjustedCost( int index )
   {
      return _AdjustedCost[index];
   }
    
   /**
    * Gets the AdjustedCost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AdjustedCost or the specified default value.
    */
   public final String getAdjustedCost( int index, String defaultValue )
   {
      return _AdjustedCost[index] == null ? defaultValue : _AdjustedCost[index];
   }
    
   /**
    * Gets the array of AdjustedCost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AdjustedCost values.
    */
   public final String[] getAdjustedCostArray()
   {
      return _AdjustedCost;
   }
    
   /**
    * Gets the ACBPerUnit field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ACBPerUnit or null.
    */
   public final String getACBPerUnit( int index )
   {
      return _ACBPerUnit[index];
   }
    
   /**
    * Gets the ACBPerUnit field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ACBPerUnit or the specified default value.
    */
   public final String getACBPerUnit( int index, String defaultValue )
   {
      return _ACBPerUnit[index] == null ? defaultValue : _ACBPerUnit[index];
   }
    
   /**
    * Gets the array of ACBPerUnit fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ACBPerUnit values.
    */
   public final String[] getACBPerUnitArray()
   {
      return _ACBPerUnit;
   }
    
   /**
    * Gets the GainOrLossAmt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GainOrLossAmt or null.
    */
   public final String getGainOrLossAmt( int index )
   {
      return _GainOrLossAmt[index];
   }
    
   /**
    * Gets the GainOrLossAmt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GainOrLossAmt or the specified default value.
    */
   public final String getGainOrLossAmt( int index, String defaultValue )
   {
      return _GainOrLossAmt[index] == null ? defaultValue : _GainOrLossAmt[index];
   }
    
   /**
    * Gets the array of GainOrLossAmt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GainOrLossAmt values.
    */
   public final String[] getGainOrLossAmtArray()
   {
      return _GainOrLossAmt;
   }
    
   /**
    * Gets the Trans type description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trans type description or null.
    */
   public final String getTransTypeDesc( int index )
   {
      return _TransTypeDesc[index];
   }
    
   /**
    * Gets the Trans type description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trans type description or the specified default value.
    */
   public final String getTransTypeDesc( int index, String defaultValue )
   {
      return _TransTypeDesc[index] == null ? defaultValue : _TransTypeDesc[index];
   }
    
   /**
    * Gets the array of Trans type description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trans type description values.
    */
   public final String[] getTransTypeDescArray()
   {
      return _TransTypeDesc;
   }
    
   /**
    * Gets the Trans Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trans Type or null.
    */
   public final String getTransType( int index )
   {
      return _TransType[index];
   }
    
   /**
    * Gets the Trans Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trans Type or the specified default value.
    */
   public final String getTransType( int index, String defaultValue )
   {
      return _TransType[index] == null ? defaultValue : _TransType[index];
   }
    
   /**
    * Gets the array of Trans Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trans Type values.
    */
   public final String[] getTransTypeArray()
   {
      return _TransType;
   }
    
   /**
    * Gets the Historical Unit ACB field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Historical Unit ACB or null.
    */
   public final String getHistUnitACB( int index )
   {
      return _HistUnitACB[index];
   }
    
   /**
    * Gets the Historical Unit ACB field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Historical Unit ACB or the specified default value.
    */
   public final String getHistUnitACB( int index, String defaultValue )
   {
      return _HistUnitACB[index] == null ? defaultValue : _HistUnitACB[index];
   }
    
   /**
    * Gets the array of Historical Unit ACB fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Historical Unit ACB values.
    */
   public final String[] getHistUnitACBArray()
   {
      return _HistUnitACB;
   }
    
   /**
    * Gets the ACB offset value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ACB offset value or null.
    */
   public final String getACBOffset( int index )
   {
      return _ACBOffset[index];
   }
    
   /**
    * Gets the ACB offset value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ACB offset value or the specified default value.
    */
   public final String getACBOffset( int index, String defaultValue )
   {
      return _ACBOffset[index] == null ? defaultValue : _ACBOffset[index];
   }
    
   /**
    * Gets the array of ACB offset value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ACB offset value values.
    */
   public final String[] getACBOffsetArray()
   {
      return _ACBOffset;
   }
    
   /**
    * Gets the ACB Transaction Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ACB Transaction Id or null.
    */
   public final String getACBTransId( int index )
   {
      return _ACBTransId[index];
   }
    
   /**
    * Gets the ACB Transaction Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ACB Transaction Id or the specified default value.
    */
   public final String getACBTransId( int index, String defaultValue )
   {
      return _ACBTransId[index] == null ? defaultValue : _ACBTransId[index];
   }
    
   /**
    * Gets the array of ACB Transaction Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ACB Transaction Id values.
    */
   public final String[] getACBTransIdArray()
   {
      return _ACBTransId;
   }
    
   /**
    * Gets the Taxable Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Taxable Amount or null.
    */
   public final String getTaxableAmount( int index )
   {
      return _TaxableAmount[index];
   }
    
   /**
    * Gets the Taxable Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Taxable Amount or the specified default value.
    */
   public final String getTaxableAmount( int index, String defaultValue )
   {
      return _TaxableAmount[index] == null ? defaultValue : _TaxableAmount[index];
   }
    
   /**
    * Gets the array of Taxable Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Taxable Amount values.
    */
   public final String[] getTaxableAmountArray()
   {
      return _TaxableAmount;
   }
    
   /**
    * Gets the Opening Market Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Opening Market Value or null.
    */
   public final String getOpeningMV( int index )
   {
      return _OpeningMV[index];
   }
    
   /**
    * Gets the Opening Market Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Opening Market Value or the specified default value.
    */
   public final String getOpeningMV( int index, String defaultValue )
   {
      return _OpeningMV[index] == null ? defaultValue : _OpeningMV[index];
   }
    
   /**
    * Gets the array of Opening Market Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Opening Market Value values.
    */
   public final String[] getOpeningMVArray()
   {
      return _OpeningMV;
   }
    
   /**
    * Gets the GainOrLossCurrency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GainOrLossCurrency or null.
    */
   public final String getGainOrLossCurrency( int index )
   {
      return _GainOrLossCurrency[index];
   }
    
   /**
    * Gets the GainOrLossCurrency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GainOrLossCurrency or the specified default value.
    */
   public final String getGainOrLossCurrency( int index, String defaultValue )
   {
      return _GainOrLossCurrency[index] == null ? defaultValue : _GainOrLossCurrency[index];
   }
    
   /**
    * Gets the array of GainOrLossCurrency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GainOrLossCurrency values.
    */
   public final String[] getGainOrLossCurrencyArray()
   {
      return _GainOrLossCurrency;
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
      _CurrencyName = responseBuffer.decodeString(responseBuffer.getNextField());
      _ACBPlugAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _ACBPlugDate = responseBuffer.decodeDate(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _TradeDate = resizeArray( _TradeDate, _RepeatCount );
      _TransAmount = resizeArray( _TransAmount, _RepeatCount );
      _Units = resizeArray( _Units, _RepeatCount );
      _UnitsHeld = resizeArray( _UnitsHeld, _RepeatCount );
      _AdjustedCost = resizeArray( _AdjustedCost, _RepeatCount );
      _ACBPerUnit = resizeArray( _ACBPerUnit, _RepeatCount );
      _GainOrLossAmt = resizeArray( _GainOrLossAmt, _RepeatCount );
      _TransTypeDesc = resizeArray( _TransTypeDesc, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _HistUnitACB = resizeArray( _HistUnitACB, _RepeatCount );
      _ACBOffset = resizeArray( _ACBOffset, _RepeatCount );
      _ACBTransId = resizeArray( _ACBTransId, _RepeatCount );
      _TaxableAmount = resizeArray( _TaxableAmount, _RepeatCount );
      _OpeningMV = resizeArray( _OpeningMV, _RepeatCount );
      _GainOrLossCurrency = resizeArray( _GainOrLossCurrency, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradeDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TransAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Units[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitsHeld[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AdjustedCost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ACBPerUnit[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GainOrLossAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _HistUnitACB[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ACBOffset[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ACBTransId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxableAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OpeningMV[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GainOrLossCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
