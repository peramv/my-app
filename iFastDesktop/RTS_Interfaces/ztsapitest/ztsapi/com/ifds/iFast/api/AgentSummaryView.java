
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Agent Summary view.
 * For additional view information see <A HREF="../../../../viewspecs/AgentSummary.doc">AgentSummary.doc</A>.
 * 
 * @author RTS Generated
 */
public class AgentSummaryView extends IFastView implements Serializable
{

   /**
    * Sales rep total member variable.
    */
   private String _SlsRepTotal = null;
   
   private int _RepeatCount = 0;
   
   /**
    * FundCode member array.
    */
   private String[] _FundCode = null;
   
   /**
    * ClassCode member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Fund Percentage member array.
    */
   private String[] _FundPercent = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Unit Value member array.
    */
   private String[] _UnitValue = null;
   
   /**
    * Fund Settled Units member array.
    */
   private String[] _FundSettUnits = null;
   
   /**
    * Fund Settled Amount member array.
    */
   private String[] _FundSettAmt = null;
   
   /**
    * TaxType Description member array.
    */
   private String[] _TaxTypeDesc = null;
   
   /**
    * Percentage of fund by product member array.
    */
   private String[] _FundProdPercent = null;
   
   /**
    * Total Settled Units in fund by product member array.
    */
   private String[] _FundProdSettUnits = null;
   
   /**
    * Settled Fund in Product Amount member array.
    */
   private String[] _FundProdSettAmt = null;
   
   /**
    * Valuation Date member array.
    */
   private Date[] _ValueAsAt = null;
   
   /**
    * Tax Type member array.
    */
   private String[] _TaxType = null;
   
   /**
    * Currency Total member array.
    */
   private String[] _CurrTotal = null;
   
   /**
    * FundGroup member array.
    */
   private String[] _FundGroup = null;
   
   /**
    * FundUnsettUnits member array.
    */
   private String[] _FundUnsettUnits = null;
   
   /**
    * FundUnsettAmt member array.
    */
   private String[] _FundUnsettAmt = null;
   
   /**
    * FundProdUnsettUnits member array.
    */
   private String[] _FundProdUnsettUnits = null;
   
   /**
    * FundProdUnsettAmt member array.
    */
   private String[] _FundProdUnsettAmt = null;
   
   /**
    * FundTotalUnits member array.
    */
   private String[] _FundTotalUnits = null;
   
   /**
    * FundTotalAmt member array.
    */
   private String[] _FundTotalAmt = null;
   
   /**
    * FundProdTotalUnits member array.
    */
   private String[] _FundProdTotalUnits = null;
   
   /**
    * FundProdTotalAmt member array.
    */
   private String[] _FundProdTotalAmt = null;
   
   /**
    * CurrSettValue member array.
    */
   private String[] _CurrSettValue = null;
   
   /**
    * CurrUnsettValue member array.
    */
   private String[] _CurrUnsettValue = null;
   
   /**
    * From Date for Pending Trade Inquiry member array.
    */
   private Date[] _LastNR = null;
   
   /**
    * To Date for Pending Trade Inquiry member array.
    */
   private Date[] _NextNR = null;
   
   /**
    * Total of Pending Trade member array.
    */
   private String[] _PendingTradeTotal = null;
   

   /**
    * Constructs the AgentSummaryView object.
    * 
    */
   public AgentSummaryView()
   {
      super ( new AgentSummaryRequest() );
   }

   /**
    * Constructs the AgentSummaryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AgentSummaryView( String hostEncoding )
   {
      super ( new AgentSummaryRequest( hostEncoding ) );
   }

   /**
    * Gets the AgentSummaryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AgentSummaryRequest object.
    */
   public final AgentSummaryRequest getRequest()
   {
      return (AgentSummaryRequest)getIFastRequest();
   }
        
   /**
    * Gets the Sales rep total field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Sales rep total or null.
    */
   public final String getSlsRepTotal()
   {
      return _SlsRepTotal;
   }
	
   /**
    * Gets the Sales rep total field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales rep total or the specified default value.
    */
   public final String getSlsRepTotal( String defaultValue )
   {
      return _SlsRepTotal == null ? defaultValue : _SlsRepTotal;
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
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the FundCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundCode or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of FundCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundCode values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the ClassCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ClassCode or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the ClassCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ClassCode or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of ClassCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ClassCode values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
   }
    
   /**
    * Gets the Fund Percentage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Percentage or null.
    */
   public final String getFundPercent( int index )
   {
      return _FundPercent[index];
   }
    
   /**
    * Gets the Fund Percentage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Percentage or the specified default value.
    */
   public final String getFundPercent( int index, String defaultValue )
   {
      return _FundPercent[index] == null ? defaultValue : _FundPercent[index];
   }
    
   /**
    * Gets the array of Fund Percentage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Percentage values.
    */
   public final String[] getFundPercentArray()
   {
      return _FundPercent;
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency or null.
    */
   public final String getCurrency( int index )
   {
      return _Currency[index];
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency or the specified default value.
    */
   public final String getCurrency( int index, String defaultValue )
   {
      return _Currency[index] == null ? defaultValue : _Currency[index];
   }
    
   /**
    * Gets the array of Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency values.
    */
   public final String[] getCurrencyArray()
   {
      return _Currency;
   }
    
   /**
    * Gets the Unit Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unit Value or null.
    */
   public final String getUnitValue( int index )
   {
      return _UnitValue[index];
   }
    
   /**
    * Gets the Unit Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unit Value or the specified default value.
    */
   public final String getUnitValue( int index, String defaultValue )
   {
      return _UnitValue[index] == null ? defaultValue : _UnitValue[index];
   }
    
   /**
    * Gets the array of Unit Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unit Value values.
    */
   public final String[] getUnitValueArray()
   {
      return _UnitValue;
   }
    
   /**
    * Gets the Fund Settled Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Settled Units or null.
    */
   public final String getFundSettUnits( int index )
   {
      return _FundSettUnits[index];
   }
    
   /**
    * Gets the Fund Settled Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Settled Units or the specified default value.
    */
   public final String getFundSettUnits( int index, String defaultValue )
   {
      return _FundSettUnits[index] == null ? defaultValue : _FundSettUnits[index];
   }
    
   /**
    * Gets the array of Fund Settled Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Settled Units values.
    */
   public final String[] getFundSettUnitsArray()
   {
      return _FundSettUnits;
   }
    
   /**
    * Gets the Fund Settled Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Settled Amount or null.
    */
   public final String getFundSettAmt( int index )
   {
      return _FundSettAmt[index];
   }
    
   /**
    * Gets the Fund Settled Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Settled Amount or the specified default value.
    */
   public final String getFundSettAmt( int index, String defaultValue )
   {
      return _FundSettAmt[index] == null ? defaultValue : _FundSettAmt[index];
   }
    
   /**
    * Gets the array of Fund Settled Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Settled Amount values.
    */
   public final String[] getFundSettAmtArray()
   {
      return _FundSettAmt;
   }
    
   /**
    * Gets the TaxType Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TaxType Description or null.
    */
   public final String getTaxTypeDesc( int index )
   {
      return _TaxTypeDesc[index];
   }
    
   /**
    * Gets the TaxType Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TaxType Description or the specified default value.
    */
   public final String getTaxTypeDesc( int index, String defaultValue )
   {
      return _TaxTypeDesc[index] == null ? defaultValue : _TaxTypeDesc[index];
   }
    
   /**
    * Gets the array of TaxType Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TaxType Description values.
    */
   public final String[] getTaxTypeDescArray()
   {
      return _TaxTypeDesc;
   }
    
   /**
    * Gets the Percentage of fund by product field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Percentage of fund by product or null.
    */
   public final String getFundProdPercent( int index )
   {
      return _FundProdPercent[index];
   }
    
   /**
    * Gets the Percentage of fund by product field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percentage of fund by product or the specified default value.
    */
   public final String getFundProdPercent( int index, String defaultValue )
   {
      return _FundProdPercent[index] == null ? defaultValue : _FundProdPercent[index];
   }
    
   /**
    * Gets the array of Percentage of fund by product fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Percentage of fund by product values.
    */
   public final String[] getFundProdPercentArray()
   {
      return _FundProdPercent;
   }
    
   /**
    * Gets the Total Settled Units in fund by product field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Total Settled Units in fund by product or null.
    */
   public final String getFundProdSettUnits( int index )
   {
      return _FundProdSettUnits[index];
   }
    
   /**
    * Gets the Total Settled Units in fund by product field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Settled Units in fund by product or the specified default value.
    */
   public final String getFundProdSettUnits( int index, String defaultValue )
   {
      return _FundProdSettUnits[index] == null ? defaultValue : _FundProdSettUnits[index];
   }
    
   /**
    * Gets the array of Total Settled Units in fund by product fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Total Settled Units in fund by product values.
    */
   public final String[] getFundProdSettUnitsArray()
   {
      return _FundProdSettUnits;
   }
    
   /**
    * Gets the Settled Fund in Product Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settled Fund in Product Amount or null.
    */
   public final String getFundProdSettAmt( int index )
   {
      return _FundProdSettAmt[index];
   }
    
   /**
    * Gets the Settled Fund in Product Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settled Fund in Product Amount or the specified default value.
    */
   public final String getFundProdSettAmt( int index, String defaultValue )
   {
      return _FundProdSettAmt[index] == null ? defaultValue : _FundProdSettAmt[index];
   }
    
   /**
    * Gets the array of Settled Fund in Product Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settled Fund in Product Amount values.
    */
   public final String[] getFundProdSettAmtArray()
   {
      return _FundProdSettAmt;
   }
    
   /**
    * Gets the Valuation Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Valuation Date or null.
    */
   public final Date getValueAsAt( int index )
   {
      return _ValueAsAt[index];
   }
    
   /**
    * Gets the Valuation Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Valuation Date or the specified default value.
    */
   public final Date getValueAsAt( int index, Date defaultValue )
   {
      return _ValueAsAt[index] == null ? defaultValue : _ValueAsAt[index];
   }
    
   /**
    * Gets the array of Valuation Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Valuation Date values.
    */
   public final Date[] getValueAsAtArray()
   {
      return _ValueAsAt;
   }
    
   /**
    * Gets the Tax Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Type or null.
    */
   public final String getTaxType( int index )
   {
      return _TaxType[index];
   }
    
   /**
    * Gets the Tax Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type or the specified default value.
    */
   public final String getTaxType( int index, String defaultValue )
   {
      return _TaxType[index] == null ? defaultValue : _TaxType[index];
   }
    
   /**
    * Gets the array of Tax Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Type values.
    */
   public final String[] getTaxTypeArray()
   {
      return _TaxType;
   }
    
   /**
    * Gets the Currency Total field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency Total or null.
    */
   public final String getCurrTotal( int index )
   {
      return _CurrTotal[index];
   }
    
   /**
    * Gets the Currency Total field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency Total or the specified default value.
    */
   public final String getCurrTotal( int index, String defaultValue )
   {
      return _CurrTotal[index] == null ? defaultValue : _CurrTotal[index];
   }
    
   /**
    * Gets the array of Currency Total fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency Total values.
    */
   public final String[] getCurrTotalArray()
   {
      return _CurrTotal;
   }
    
   /**
    * Gets the FundGroup field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundGroup or null.
    */
   public final String getFundGroup( int index )
   {
      return _FundGroup[index];
   }
    
   /**
    * Gets the FundGroup field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundGroup or the specified default value.
    */
   public final String getFundGroup( int index, String defaultValue )
   {
      return _FundGroup[index] == null ? defaultValue : _FundGroup[index];
   }
    
   /**
    * Gets the array of FundGroup fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundGroup values.
    */
   public final String[] getFundGroupArray()
   {
      return _FundGroup;
   }
    
   /**
    * Gets the FundUnsettUnits field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundUnsettUnits or null.
    */
   public final String getFundUnsettUnits( int index )
   {
      return _FundUnsettUnits[index];
   }
    
   /**
    * Gets the FundUnsettUnits field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundUnsettUnits or the specified default value.
    */
   public final String getFundUnsettUnits( int index, String defaultValue )
   {
      return _FundUnsettUnits[index] == null ? defaultValue : _FundUnsettUnits[index];
   }
    
   /**
    * Gets the array of FundUnsettUnits fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundUnsettUnits values.
    */
   public final String[] getFundUnsettUnitsArray()
   {
      return _FundUnsettUnits;
   }
    
   /**
    * Gets the FundUnsettAmt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundUnsettAmt or null.
    */
   public final String getFundUnsettAmt( int index )
   {
      return _FundUnsettAmt[index];
   }
    
   /**
    * Gets the FundUnsettAmt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundUnsettAmt or the specified default value.
    */
   public final String getFundUnsettAmt( int index, String defaultValue )
   {
      return _FundUnsettAmt[index] == null ? defaultValue : _FundUnsettAmt[index];
   }
    
   /**
    * Gets the array of FundUnsettAmt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundUnsettAmt values.
    */
   public final String[] getFundUnsettAmtArray()
   {
      return _FundUnsettAmt;
   }
    
   /**
    * Gets the FundProdUnsettUnits field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundProdUnsettUnits or null.
    */
   public final String getFundProdUnsettUnits( int index )
   {
      return _FundProdUnsettUnits[index];
   }
    
   /**
    * Gets the FundProdUnsettUnits field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundProdUnsettUnits or the specified default value.
    */
   public final String getFundProdUnsettUnits( int index, String defaultValue )
   {
      return _FundProdUnsettUnits[index] == null ? defaultValue : _FundProdUnsettUnits[index];
   }
    
   /**
    * Gets the array of FundProdUnsettUnits fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundProdUnsettUnits values.
    */
   public final String[] getFundProdUnsettUnitsArray()
   {
      return _FundProdUnsettUnits;
   }
    
   /**
    * Gets the FundProdUnsettAmt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundProdUnsettAmt or null.
    */
   public final String getFundProdUnsettAmt( int index )
   {
      return _FundProdUnsettAmt[index];
   }
    
   /**
    * Gets the FundProdUnsettAmt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundProdUnsettAmt or the specified default value.
    */
   public final String getFundProdUnsettAmt( int index, String defaultValue )
   {
      return _FundProdUnsettAmt[index] == null ? defaultValue : _FundProdUnsettAmt[index];
   }
    
   /**
    * Gets the array of FundProdUnsettAmt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundProdUnsettAmt values.
    */
   public final String[] getFundProdUnsettAmtArray()
   {
      return _FundProdUnsettAmt;
   }
    
   /**
    * Gets the FundTotalUnits field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundTotalUnits or null.
    */
   public final String getFundTotalUnits( int index )
   {
      return _FundTotalUnits[index];
   }
    
   /**
    * Gets the FundTotalUnits field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundTotalUnits or the specified default value.
    */
   public final String getFundTotalUnits( int index, String defaultValue )
   {
      return _FundTotalUnits[index] == null ? defaultValue : _FundTotalUnits[index];
   }
    
   /**
    * Gets the array of FundTotalUnits fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundTotalUnits values.
    */
   public final String[] getFundTotalUnitsArray()
   {
      return _FundTotalUnits;
   }
    
   /**
    * Gets the FundTotalAmt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundTotalAmt or null.
    */
   public final String getFundTotalAmt( int index )
   {
      return _FundTotalAmt[index];
   }
    
   /**
    * Gets the FundTotalAmt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundTotalAmt or the specified default value.
    */
   public final String getFundTotalAmt( int index, String defaultValue )
   {
      return _FundTotalAmt[index] == null ? defaultValue : _FundTotalAmt[index];
   }
    
   /**
    * Gets the array of FundTotalAmt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundTotalAmt values.
    */
   public final String[] getFundTotalAmtArray()
   {
      return _FundTotalAmt;
   }
    
   /**
    * Gets the FundProdTotalUnits field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundProdTotalUnits or null.
    */
   public final String getFundProdTotalUnits( int index )
   {
      return _FundProdTotalUnits[index];
   }
    
   /**
    * Gets the FundProdTotalUnits field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundProdTotalUnits or the specified default value.
    */
   public final String getFundProdTotalUnits( int index, String defaultValue )
   {
      return _FundProdTotalUnits[index] == null ? defaultValue : _FundProdTotalUnits[index];
   }
    
   /**
    * Gets the array of FundProdTotalUnits fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundProdTotalUnits values.
    */
   public final String[] getFundProdTotalUnitsArray()
   {
      return _FundProdTotalUnits;
   }
    
   /**
    * Gets the FundProdTotalAmt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundProdTotalAmt or null.
    */
   public final String getFundProdTotalAmt( int index )
   {
      return _FundProdTotalAmt[index];
   }
    
   /**
    * Gets the FundProdTotalAmt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundProdTotalAmt or the specified default value.
    */
   public final String getFundProdTotalAmt( int index, String defaultValue )
   {
      return _FundProdTotalAmt[index] == null ? defaultValue : _FundProdTotalAmt[index];
   }
    
   /**
    * Gets the array of FundProdTotalAmt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundProdTotalAmt values.
    */
   public final String[] getFundProdTotalAmtArray()
   {
      return _FundProdTotalAmt;
   }
    
   /**
    * Gets the CurrSettValue field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CurrSettValue or null.
    */
   public final String getCurrSettValue( int index )
   {
      return _CurrSettValue[index];
   }
    
   /**
    * Gets the CurrSettValue field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CurrSettValue or the specified default value.
    */
   public final String getCurrSettValue( int index, String defaultValue )
   {
      return _CurrSettValue[index] == null ? defaultValue : _CurrSettValue[index];
   }
    
   /**
    * Gets the array of CurrSettValue fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CurrSettValue values.
    */
   public final String[] getCurrSettValueArray()
   {
      return _CurrSettValue;
   }
    
   /**
    * Gets the CurrUnsettValue field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CurrUnsettValue or null.
    */
   public final String getCurrUnsettValue( int index )
   {
      return _CurrUnsettValue[index];
   }
    
   /**
    * Gets the CurrUnsettValue field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CurrUnsettValue or the specified default value.
    */
   public final String getCurrUnsettValue( int index, String defaultValue )
   {
      return _CurrUnsettValue[index] == null ? defaultValue : _CurrUnsettValue[index];
   }
    
   /**
    * Gets the array of CurrUnsettValue fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CurrUnsettValue values.
    */
   public final String[] getCurrUnsettValueArray()
   {
      return _CurrUnsettValue;
   }
    
   /**
    * Gets the From Date for Pending Trade Inquiry field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the From Date for Pending Trade Inquiry or null.
    */
   public final Date getLastNR( int index )
   {
      return _LastNR[index];
   }
    
   /**
    * Gets the From Date for Pending Trade Inquiry field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the From Date for Pending Trade Inquiry or the specified default value.
    */
   public final Date getLastNR( int index, Date defaultValue )
   {
      return _LastNR[index] == null ? defaultValue : _LastNR[index];
   }
    
   /**
    * Gets the array of From Date for Pending Trade Inquiry fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of From Date for Pending Trade Inquiry values.
    */
   public final Date[] getLastNRArray()
   {
      return _LastNR;
   }
    
   /**
    * Gets the To Date for Pending Trade Inquiry field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the To Date for Pending Trade Inquiry or null.
    */
   public final Date getNextNR( int index )
   {
      return _NextNR[index];
   }
    
   /**
    * Gets the To Date for Pending Trade Inquiry field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To Date for Pending Trade Inquiry or the specified default value.
    */
   public final Date getNextNR( int index, Date defaultValue )
   {
      return _NextNR[index] == null ? defaultValue : _NextNR[index];
   }
    
   /**
    * Gets the array of To Date for Pending Trade Inquiry fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of To Date for Pending Trade Inquiry values.
    */
   public final Date[] getNextNRArray()
   {
      return _NextNR;
   }
    
   /**
    * Gets the Total of Pending Trade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Total of Pending Trade or null.
    */
   public final String getPendingTradeTotal( int index )
   {
      return _PendingTradeTotal[index];
   }
    
   /**
    * Gets the Total of Pending Trade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total of Pending Trade or the specified default value.
    */
   public final String getPendingTradeTotal( int index, String defaultValue )
   {
      return _PendingTradeTotal[index] == null ? defaultValue : _PendingTradeTotal[index];
   }
    
   /**
    * Gets the array of Total of Pending Trade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Total of Pending Trade values.
    */
   public final String[] getPendingTradeTotalArray()
   {
      return _PendingTradeTotal;
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
      _SlsRepTotal = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _FundPercent = resizeArray( _FundPercent, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _UnitValue = resizeArray( _UnitValue, _RepeatCount );
      _FundSettUnits = resizeArray( _FundSettUnits, _RepeatCount );
      _FundSettAmt = resizeArray( _FundSettAmt, _RepeatCount );
      _TaxTypeDesc = resizeArray( _TaxTypeDesc, _RepeatCount );
      _FundProdPercent = resizeArray( _FundProdPercent, _RepeatCount );
      _FundProdSettUnits = resizeArray( _FundProdSettUnits, _RepeatCount );
      _FundProdSettAmt = resizeArray( _FundProdSettAmt, _RepeatCount );
      _ValueAsAt = resizeArray( _ValueAsAt, _RepeatCount );
      _TaxType = resizeArray( _TaxType, _RepeatCount );
      _CurrTotal = resizeArray( _CurrTotal, _RepeatCount );
      _FundGroup = resizeArray( _FundGroup, _RepeatCount );
      _FundUnsettUnits = resizeArray( _FundUnsettUnits, _RepeatCount );
      _FundUnsettAmt = resizeArray( _FundUnsettAmt, _RepeatCount );
      _FundProdUnsettUnits = resizeArray( _FundProdUnsettUnits, _RepeatCount );
      _FundProdUnsettAmt = resizeArray( _FundProdUnsettAmt, _RepeatCount );
      _FundTotalUnits = resizeArray( _FundTotalUnits, _RepeatCount );
      _FundTotalAmt = resizeArray( _FundTotalAmt, _RepeatCount );
      _FundProdTotalUnits = resizeArray( _FundProdTotalUnits, _RepeatCount );
      _FundProdTotalAmt = resizeArray( _FundProdTotalAmt, _RepeatCount );
      _CurrSettValue = resizeArray( _CurrSettValue, _RepeatCount );
      _CurrUnsettValue = resizeArray( _CurrUnsettValue, _RepeatCount );
      _LastNR = resizeArray( _LastNR, _RepeatCount );
      _NextNR = resizeArray( _NextNR, _RepeatCount );
      _PendingTradeTotal = resizeArray( _PendingTradeTotal, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundPercent[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundSettUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundSettAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundProdPercent[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundProdSettUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundProdSettAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ValueAsAt[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CurrTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundUnsettUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundUnsettAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundProdUnsettUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundProdUnsettAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundTotalUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundTotalAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundProdTotalUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundProdTotalAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CurrSettValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CurrUnsettValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastNR[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _NextNR[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _PendingTradeTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
