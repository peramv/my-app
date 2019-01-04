
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Inventory  Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/Inventorylnq.doc">Inventorylnq.doc</A>.
 * 
 * @author RTS Generated
 */
public class InventorylnqView extends IFastView implements Serializable
{

   /**
    * Total of Units member variable.
    */
   private String _TotalUnits = null;
   
   /**
    * Total CB Free Units member variable.
    */
   private String _TotalCBFreeUnits = null;
   
   /**
    * G1 Shares member variable.
    */
   private String _G1Shares = null;
   
   /**
    * G2 Shares member variable.
    */
   private String _G2Shares = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Inventory Summary ID member array.
    */
   private Integer[] _InvSummID = null;
   
   /**
    * Status member array.
    */
   private String[] _InvStatus = null;
   
   /**
    * Original Effective Date of record member array.
    */
   private Date[] _OrigEffectiveDate = null;
   
   /**
    * Maturity Date for DSC calculation member array.
    */
   private Date[] _MaturityDate = null;
   
   /**
    * Date record was last updated (settlement date) member array.
    */
   private Date[] _LastActivityDate = null;
   
   /**
    * Fund the money originated from or dividend was earned member array.
    */
   private String[] _FromFund = null;
   
   /**
    * From Class member array.
    */
   private String[] _FromClass = null;
   
   /**
    * Transaction Type member array.
    */
   private String[] _TransType = null;
   
   /**
    * Partnership member array.
    */
   private String[] _PShip = null;
   
   /**
    * Original purchase price per unit member array.
    */
   private String[] _OrigFundRate = null;
   
   /**
    * Original cost of units member array.
    */
   private String[] _Rate = null;
   
   /**
    * Units based on originally purchased fund member array.
    */
   private String[] _OrigFundUnits = null;
   
   /**
    * Current units from sharelot member array.
    */
   private String[] _Units = null;
   
   /**
    * Flag indicating if shares are eligible for commission member array.
    */
   private Boolean[] _Commissionable = null;
   
   /**
    * Commission Rate member array.
    */
   private String[] _CommRate = null;
   
   /**
    * LSIF Trace Number member array.
    */
   private Integer[] _TraceNo = null;
   
   /**
    * LSIF Mature Date member array.
    */
   private Date[] _MatureDate = null;
   
   /**
    * LSIF Receipt Status member array.
    */
   private String[] _ReceiptStatus = null;
   
   /**
    * LSIF Tax Jurisdiction member array.
    */
   private String[] _TaxJuris = null;
   
   /**
    * LSIF Receipt Number member array.
    */
   private Integer[] _ReceiptNumber = null;
   
   /**
    * Original Total Units member array.
    */
   private String[] _OrigTotalUnits = null;
   
   /**
    * Used Units member array.
    */
   private String[] _UsedUnits = null;
   
   /**
    * Rollover Qualification Date member array.
    */
   private Date[] _RollQualDate = null;
   
   /**
    * RDR Advice member array.
    */
   private String[] _RDRAdvice = null;
   
   /**
    * Group Original Date member array.
    */
   private Date[] _GroupOrigdate = null;
   

   /**
    * Constructs the InventorylnqView object.
    * 
    */
   public InventorylnqView()
   {
      super ( new InventorylnqRequest() );
   }

   /**
    * Constructs the InventorylnqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public InventorylnqView( String hostEncoding )
   {
      super ( new InventorylnqRequest( hostEncoding ) );
   }

   /**
    * Gets the InventorylnqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The InventorylnqRequest object.
    */
   public final InventorylnqRequest getRequest()
   {
      return (InventorylnqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Total of Units field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total of Units or null.
    */
   public final String getTotalUnits()
   {
      return _TotalUnits;
   }
	
   /**
    * Gets the Total of Units field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total of Units or the specified default value.
    */
   public final String getTotalUnits( String defaultValue )
   {
      return _TotalUnits == null ? defaultValue : _TotalUnits;
   }
                  
   /**
    * Gets the Total CB Free Units field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total CB Free Units or null.
    */
   public final String getTotalCBFreeUnits()
   {
      return _TotalCBFreeUnits;
   }
	
   /**
    * Gets the Total CB Free Units field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total CB Free Units or the specified default value.
    */
   public final String getTotalCBFreeUnits( String defaultValue )
   {
      return _TotalCBFreeUnits == null ? defaultValue : _TotalCBFreeUnits;
   }
                  
   /**
    * Gets the G1 Shares field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the G1 Shares or null.
    */
   public final String getG1Shares()
   {
      return _G1Shares;
   }
	
   /**
    * Gets the G1 Shares field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the G1 Shares or the specified default value.
    */
   public final String getG1Shares( String defaultValue )
   {
      return _G1Shares == null ? defaultValue : _G1Shares;
   }
                  
   /**
    * Gets the G2 Shares field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the G2 Shares or null.
    */
   public final String getG2Shares()
   {
      return _G2Shares;
   }
	
   /**
    * Gets the G2 Shares field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the G2 Shares or the specified default value.
    */
   public final String getG2Shares( String defaultValue )
   {
      return _G2Shares == null ? defaultValue : _G2Shares;
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
    * Gets the Inventory Summary ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Inventory Summary ID or null.
    */
   public final Integer getInvSummID( int index )
   {
      return _InvSummID[index];
   }
    
   /**
    * Gets the Inventory Summary ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Inventory Summary ID or the specified default value.
    */
   public final int getInvSummID( int index, int defaultValue )
   {
      return _InvSummID[index] == null ? defaultValue : _InvSummID[index].intValue();
   }
    
   /**
    * Gets the array of Inventory Summary ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Inventory Summary ID values.
    */
   public final Integer[] getInvSummIDArray()
   {
      return _InvSummID;
   }
    
   /**
    * Gets the Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Status or null.
    */
   public final String getInvStatus( int index )
   {
      return _InvStatus[index];
   }
    
   /**
    * Gets the Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Status or the specified default value.
    */
   public final String getInvStatus( int index, String defaultValue )
   {
      return _InvStatus[index] == null ? defaultValue : _InvStatus[index];
   }
    
   /**
    * Gets the array of Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Status values.
    */
   public final String[] getInvStatusArray()
   {
      return _InvStatus;
   }
    
   /**
    * Gets the Original Effective Date of record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Original Effective Date of record or null.
    */
   public final Date getOrigEffectiveDate( int index )
   {
      return _OrigEffectiveDate[index];
   }
    
   /**
    * Gets the Original Effective Date of record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Original Effective Date of record or the specified default value.
    */
   public final Date getOrigEffectiveDate( int index, Date defaultValue )
   {
      return _OrigEffectiveDate[index] == null ? defaultValue : _OrigEffectiveDate[index];
   }
    
   /**
    * Gets the array of Original Effective Date of record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Original Effective Date of record values.
    */
   public final Date[] getOrigEffectiveDateArray()
   {
      return _OrigEffectiveDate;
   }
    
   /**
    * Gets the Maturity Date for DSC calculation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maturity Date for DSC calculation or null.
    */
   public final Date getMaturityDate( int index )
   {
      return _MaturityDate[index];
   }
    
   /**
    * Gets the Maturity Date for DSC calculation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maturity Date for DSC calculation or the specified default value.
    */
   public final Date getMaturityDate( int index, Date defaultValue )
   {
      return _MaturityDate[index] == null ? defaultValue : _MaturityDate[index];
   }
    
   /**
    * Gets the array of Maturity Date for DSC calculation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maturity Date for DSC calculation values.
    */
   public final Date[] getMaturityDateArray()
   {
      return _MaturityDate;
   }
    
   /**
    * Gets the Date record was last updated (settlement date) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date record was last updated (settlement date) or null.
    */
   public final Date getLastActivityDate( int index )
   {
      return _LastActivityDate[index];
   }
    
   /**
    * Gets the Date record was last updated (settlement date) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date record was last updated (settlement date) or the specified default value.
    */
   public final Date getLastActivityDate( int index, Date defaultValue )
   {
      return _LastActivityDate[index] == null ? defaultValue : _LastActivityDate[index];
   }
    
   /**
    * Gets the array of Date record was last updated (settlement date) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date record was last updated (settlement date) values.
    */
   public final Date[] getLastActivityDateArray()
   {
      return _LastActivityDate;
   }
    
   /**
    * Gets the Fund the money originated from or dividend was earned field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund the money originated from or dividend was earned or null.
    */
   public final String getFromFund( int index )
   {
      return _FromFund[index];
   }
    
   /**
    * Gets the Fund the money originated from or dividend was earned field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund the money originated from or dividend was earned or the specified default value.
    */
   public final String getFromFund( int index, String defaultValue )
   {
      return _FromFund[index] == null ? defaultValue : _FromFund[index];
   }
    
   /**
    * Gets the array of Fund the money originated from or dividend was earned fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund the money originated from or dividend was earned values.
    */
   public final String[] getFromFundArray()
   {
      return _FromFund;
   }
    
   /**
    * Gets the From Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the From Class or null.
    */
   public final String getFromClass( int index )
   {
      return _FromClass[index];
   }
    
   /**
    * Gets the From Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the From Class or the specified default value.
    */
   public final String getFromClass( int index, String defaultValue )
   {
      return _FromClass[index] == null ? defaultValue : _FromClass[index];
   }
    
   /**
    * Gets the array of From Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of From Class values.
    */
   public final String[] getFromClassArray()
   {
      return _FromClass;
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Type or null.
    */
   public final String getTransType( int index )
   {
      return _TransType[index];
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Type or the specified default value.
    */
   public final String getTransType( int index, String defaultValue )
   {
      return _TransType[index] == null ? defaultValue : _TransType[index];
   }
    
   /**
    * Gets the array of Transaction Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Type values.
    */
   public final String[] getTransTypeArray()
   {
      return _TransType;
   }
    
   /**
    * Gets the Partnership field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Partnership or null.
    */
   public final String getPShip( int index )
   {
      return _PShip[index];
   }
    
   /**
    * Gets the Partnership field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Partnership or the specified default value.
    */
   public final String getPShip( int index, String defaultValue )
   {
      return _PShip[index] == null ? defaultValue : _PShip[index];
   }
    
   /**
    * Gets the array of Partnership fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Partnership values.
    */
   public final String[] getPShipArray()
   {
      return _PShip;
   }
    
   /**
    * Gets the Original purchase price per unit field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Original purchase price per unit or null.
    */
   public final String getOrigFundRate( int index )
   {
      return _OrigFundRate[index];
   }
    
   /**
    * Gets the Original purchase price per unit field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Original purchase price per unit or the specified default value.
    */
   public final String getOrigFundRate( int index, String defaultValue )
   {
      return _OrigFundRate[index] == null ? defaultValue : _OrigFundRate[index];
   }
    
   /**
    * Gets the array of Original purchase price per unit fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Original purchase price per unit values.
    */
   public final String[] getOrigFundRateArray()
   {
      return _OrigFundRate;
   }
    
   /**
    * Gets the Original cost of units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Original cost of units or null.
    */
   public final String getRate( int index )
   {
      return _Rate[index];
   }
    
   /**
    * Gets the Original cost of units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Original cost of units or the specified default value.
    */
   public final String getRate( int index, String defaultValue )
   {
      return _Rate[index] == null ? defaultValue : _Rate[index];
   }
    
   /**
    * Gets the array of Original cost of units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Original cost of units values.
    */
   public final String[] getRateArray()
   {
      return _Rate;
   }
    
   /**
    * Gets the Units based on originally purchased fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Units based on originally purchased fund or null.
    */
   public final String getOrigFundUnits( int index )
   {
      return _OrigFundUnits[index];
   }
    
   /**
    * Gets the Units based on originally purchased fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Units based on originally purchased fund or the specified default value.
    */
   public final String getOrigFundUnits( int index, String defaultValue )
   {
      return _OrigFundUnits[index] == null ? defaultValue : _OrigFundUnits[index];
   }
    
   /**
    * Gets the array of Units based on originally purchased fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Units based on originally purchased fund values.
    */
   public final String[] getOrigFundUnitsArray()
   {
      return _OrigFundUnits;
   }
    
   /**
    * Gets the Current units from sharelot field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Current units from sharelot or null.
    */
   public final String getUnits( int index )
   {
      return _Units[index];
   }
    
   /**
    * Gets the Current units from sharelot field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Current units from sharelot or the specified default value.
    */
   public final String getUnits( int index, String defaultValue )
   {
      return _Units[index] == null ? defaultValue : _Units[index];
   }
    
   /**
    * Gets the array of Current units from sharelot fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Current units from sharelot values.
    */
   public final String[] getUnitsArray()
   {
      return _Units;
   }
    
   /**
    * Gets the Flag indicating if shares are eligible for commission field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if shares are eligible for commission or null.
    */
   public final Boolean getCommissionable( int index )
   {
      return _Commissionable[index];
   }
    
   /**
    * Gets the Flag indicating if shares are eligible for commission field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if shares are eligible for commission or the specified default value.
    */
   public final boolean getCommissionable( int index, boolean defaultValue )
   {
      return _Commissionable[index] == null ? defaultValue : _Commissionable[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if shares are eligible for commission fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if shares are eligible for commission values.
    */
   public final Boolean[] getCommissionableArray()
   {
      return _Commissionable;
   }
    
   /**
    * Gets the Commission Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission Rate or null.
    */
   public final String getCommRate( int index )
   {
      return _CommRate[index];
   }
    
   /**
    * Gets the Commission Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Rate or the specified default value.
    */
   public final String getCommRate( int index, String defaultValue )
   {
      return _CommRate[index] == null ? defaultValue : _CommRate[index];
   }
    
   /**
    * Gets the array of Commission Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Rate values.
    */
   public final String[] getCommRateArray()
   {
      return _CommRate;
   }
    
   /**
    * Gets the LSIF Trace Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LSIF Trace Number or null.
    */
   public final Integer getTraceNo( int index )
   {
      return _TraceNo[index];
   }
    
   /**
    * Gets the LSIF Trace Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LSIF Trace Number or the specified default value.
    */
   public final int getTraceNo( int index, int defaultValue )
   {
      return _TraceNo[index] == null ? defaultValue : _TraceNo[index].intValue();
   }
    
   /**
    * Gets the array of LSIF Trace Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LSIF Trace Number values.
    */
   public final Integer[] getTraceNoArray()
   {
      return _TraceNo;
   }
    
   /**
    * Gets the LSIF Mature Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LSIF Mature Date or null.
    */
   public final Date getMatureDate( int index )
   {
      return _MatureDate[index];
   }
    
   /**
    * Gets the LSIF Mature Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LSIF Mature Date or the specified default value.
    */
   public final Date getMatureDate( int index, Date defaultValue )
   {
      return _MatureDate[index] == null ? defaultValue : _MatureDate[index];
   }
    
   /**
    * Gets the array of LSIF Mature Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LSIF Mature Date values.
    */
   public final Date[] getMatureDateArray()
   {
      return _MatureDate;
   }
    
   /**
    * Gets the LSIF Receipt Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LSIF Receipt Status or null.
    */
   public final String getReceiptStatus( int index )
   {
      return _ReceiptStatus[index];
   }
    
   /**
    * Gets the LSIF Receipt Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LSIF Receipt Status or the specified default value.
    */
   public final String getReceiptStatus( int index, String defaultValue )
   {
      return _ReceiptStatus[index] == null ? defaultValue : _ReceiptStatus[index];
   }
    
   /**
    * Gets the array of LSIF Receipt Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LSIF Receipt Status values.
    */
   public final String[] getReceiptStatusArray()
   {
      return _ReceiptStatus;
   }
    
   /**
    * Gets the LSIF Tax Jurisdiction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LSIF Tax Jurisdiction or null.
    */
   public final String getTaxJuris( int index )
   {
      return _TaxJuris[index];
   }
    
   /**
    * Gets the LSIF Tax Jurisdiction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LSIF Tax Jurisdiction or the specified default value.
    */
   public final String getTaxJuris( int index, String defaultValue )
   {
      return _TaxJuris[index] == null ? defaultValue : _TaxJuris[index];
   }
    
   /**
    * Gets the array of LSIF Tax Jurisdiction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LSIF Tax Jurisdiction values.
    */
   public final String[] getTaxJurisArray()
   {
      return _TaxJuris;
   }
    
   /**
    * Gets the LSIF Receipt Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LSIF Receipt Number or null.
    */
   public final Integer getReceiptNumber( int index )
   {
      return _ReceiptNumber[index];
   }
    
   /**
    * Gets the LSIF Receipt Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LSIF Receipt Number or the specified default value.
    */
   public final int getReceiptNumber( int index, int defaultValue )
   {
      return _ReceiptNumber[index] == null ? defaultValue : _ReceiptNumber[index].intValue();
   }
    
   /**
    * Gets the array of LSIF Receipt Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LSIF Receipt Number values.
    */
   public final Integer[] getReceiptNumberArray()
   {
      return _ReceiptNumber;
   }
    
   /**
    * Gets the Original Total Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Original Total Units or null.
    */
   public final String getOrigTotalUnits( int index )
   {
      return _OrigTotalUnits[index];
   }
    
   /**
    * Gets the Original Total Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Original Total Units or the specified default value.
    */
   public final String getOrigTotalUnits( int index, String defaultValue )
   {
      return _OrigTotalUnits[index] == null ? defaultValue : _OrigTotalUnits[index];
   }
    
   /**
    * Gets the array of Original Total Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Original Total Units values.
    */
   public final String[] getOrigTotalUnitsArray()
   {
      return _OrigTotalUnits;
   }
    
   /**
    * Gets the Used Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Used Units or null.
    */
   public final String getUsedUnits( int index )
   {
      return _UsedUnits[index];
   }
    
   /**
    * Gets the Used Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Used Units or the specified default value.
    */
   public final String getUsedUnits( int index, String defaultValue )
   {
      return _UsedUnits[index] == null ? defaultValue : _UsedUnits[index];
   }
    
   /**
    * Gets the array of Used Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Used Units values.
    */
   public final String[] getUsedUnitsArray()
   {
      return _UsedUnits;
   }
    
   /**
    * Gets the Rollover Qualification Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rollover Qualification Date or null.
    */
   public final Date getRollQualDate( int index )
   {
      return _RollQualDate[index];
   }
    
   /**
    * Gets the Rollover Qualification Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rollover Qualification Date or the specified default value.
    */
   public final Date getRollQualDate( int index, Date defaultValue )
   {
      return _RollQualDate[index] == null ? defaultValue : _RollQualDate[index];
   }
    
   /**
    * Gets the array of Rollover Qualification Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rollover Qualification Date values.
    */
   public final Date[] getRollQualDateArray()
   {
      return _RollQualDate;
   }
    
   /**
    * Gets the RDR Advice field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RDR Advice or null.
    */
   public final String getRDRAdvice( int index )
   {
      return _RDRAdvice[index];
   }
    
   /**
    * Gets the RDR Advice field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RDR Advice or the specified default value.
    */
   public final String getRDRAdvice( int index, String defaultValue )
   {
      return _RDRAdvice[index] == null ? defaultValue : _RDRAdvice[index];
   }
    
   /**
    * Gets the array of RDR Advice fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RDR Advice values.
    */
   public final String[] getRDRAdviceArray()
   {
      return _RDRAdvice;
   }
    
   /**
    * Gets the Group Original Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Group Original Date or null.
    */
   public final Date getGroupOrigdate( int index )
   {
      return _GroupOrigdate[index];
   }
    
   /**
    * Gets the Group Original Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Group Original Date or the specified default value.
    */
   public final Date getGroupOrigdate( int index, Date defaultValue )
   {
      return _GroupOrigdate[index] == null ? defaultValue : _GroupOrigdate[index];
   }
    
   /**
    * Gets the array of Group Original Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Group Original Date values.
    */
   public final Date[] getGroupOrigdateArray()
   {
      return _GroupOrigdate;
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
      _TotalUnits = responseBuffer.decodeString(responseBuffer.getNextField());
      _TotalCBFreeUnits = responseBuffer.decodeString(responseBuffer.getNextField());
      _G1Shares = responseBuffer.decodeString(responseBuffer.getNextField());
      _G2Shares = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _InvSummID = resizeArray( _InvSummID, _RepeatCount );
      _InvStatus = resizeArray( _InvStatus, _RepeatCount );
      _OrigEffectiveDate = resizeArray( _OrigEffectiveDate, _RepeatCount );
      _MaturityDate = resizeArray( _MaturityDate, _RepeatCount );
      _LastActivityDate = resizeArray( _LastActivityDate, _RepeatCount );
      _FromFund = resizeArray( _FromFund, _RepeatCount );
      _FromClass = resizeArray( _FromClass, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _PShip = resizeArray( _PShip, _RepeatCount );
      _OrigFundRate = resizeArray( _OrigFundRate, _RepeatCount );
      _Rate = resizeArray( _Rate, _RepeatCount );
      _OrigFundUnits = resizeArray( _OrigFundUnits, _RepeatCount );
      _Units = resizeArray( _Units, _RepeatCount );
      _Commissionable = resizeArray( _Commissionable, _RepeatCount );
      _CommRate = resizeArray( _CommRate, _RepeatCount );
      _TraceNo = resizeArray( _TraceNo, _RepeatCount );
      _MatureDate = resizeArray( _MatureDate, _RepeatCount );
      _ReceiptStatus = resizeArray( _ReceiptStatus, _RepeatCount );
      _TaxJuris = resizeArray( _TaxJuris, _RepeatCount );
      _ReceiptNumber = resizeArray( _ReceiptNumber, _RepeatCount );
      _OrigTotalUnits = resizeArray( _OrigTotalUnits, _RepeatCount );
      _UsedUnits = resizeArray( _UsedUnits, _RepeatCount );
      _RollQualDate = resizeArray( _RollQualDate, _RepeatCount );
      _RDRAdvice = resizeArray( _RDRAdvice, _RepeatCount );
      _GroupOrigdate = resizeArray( _GroupOrigdate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _InvSummID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _InvStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OrigEffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _MaturityDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _LastActivityDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FromFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FromClass[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PShip[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OrigFundRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Rate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OrigFundUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Units[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Commissionable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CommRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TraceNo[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _MatureDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ReceiptStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxJuris[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReceiptNumber[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _OrigTotalUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UsedUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RollQualDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _RDRAdvice[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GroupOrigdate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
