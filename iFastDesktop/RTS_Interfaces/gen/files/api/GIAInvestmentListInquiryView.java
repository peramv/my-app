
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * GIA Investment List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/GIAInvestmentListInquiry.doc">GIAInvestmentListInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class GIAInvestmentListInquiryView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * IntInvestUUID member array.
    */
   private String[] _IntInvestUUID = null;
   
   /**
    * Fund member array.
    */
   private String[] _Fund = null;
   
   /**
    * Class member array.
    */
   private String[] _Class = null;
   
   /**
    * TransNum member array.
    */
   private Integer[] _TransNum = null;
   
   /**
    * TransId member array.
    */
   private String[] _TransId = null;
   
   /**
    * InvestmentNo member array.
    */
   private String[] _InvestmentNo = null;
   
   /**
    * InvestStatus member array.
    */
   private String[] _InvestStatus = null;
   
   /**
    * IntCalcMthd member array.
    */
   private String[] _IntCalcMthd = null;
   
   /**
    * IntInvestType member array.
    */
   private String[] _IntInvestType = null;
   
   /**
    * InvestTerm member array.
    */
   private Integer[] _InvestTerm = null;
   
   /**
    * IntRate member array.
    */
   private String[] _IntRate = null;
   
   /**
    * DepositDate member array.
    */
   private Date[] _DepositDate = null;
   
   /**
    * MaturityDate member array.
    */
   private Date[] _MaturityDate = null;
   
   /**
    * GIAmount member array.
    */
   private String[] _GIAmount = null;
   
   /**
    * IntCredFreq member array.
    */
   private String[] _IntCredFreq = null;
   
   /**
    * CurrentMKV member array.
    */
   private String[] _CurrentMKV = null;
   
   /**
    * LastIntCredDate member array.
    */
   private Date[] _LastIntCredDate = null;
   
   /**
    * IntAccruedToDate member array.
    */
   private String[] _IntAccruedToDate = null;
   
   /**
    * Moddate member array.
    */
   private Date[] _Moddate = null;
   
   /**
    * Moduser member array.
    */
   private String[] _Moduser = null;
   
   /**
    * Username member array.
    */
   private String[] _Username = null;
   
   /**
    * Version member array.
    */
   private Integer[] _Version = null;
   
   /**
    * LotId member array.
    */
   private String[] _LotId = null;
   
   /**
    * IntInvestId member array.
    */
   private String[] _IntInvestId = null;
   
   /**
    * PrincipalAmt member array.
    */
   private String[] _PrincipalAmt = null;
   
   /**
    * MarketValue member array.
    */
   private String[] _MarketValue = null;
   
   /**
    * ValueAtMaturity member array.
    */
   private String[] _ValueAtMaturity = null;
   
   /**
    * SelInvAmtType member array.
    */
   private String[] _SelInvAmtType = null;
   
   /**
    * SelInvAmount member array.
    */
   private String[] _SelInvAmount = null;
   
   /**
    * PrincipalRedeem member array.
    */
   private String[] _PrincipalRedeem = null;
   
   /**
    * AccruedInt member array.
    */
   private String[] _AccruedInt = null;
   
   /**
    * AdminFee member array.
    */
   private String[] _AdminFee = null;
   
   /**
    * MVA member array.
    */
   private String[] _MVA = null;
   
   /**
    * AmountNet member array.
    */
   private String[] _AmountNet = null;
   
   /**
    * InvSummId member array.
    */
   private Integer[] _InvSummId = null;
   
   /**
    * IsSelected member array.
    */
   private Boolean[] _IsSelected = null;
   
   /**
    * IntRateType member array.
    */
   private String[] _IntRateType = null;
   
   /**
    * Additional Amount member array.
    */
   private String[] _AddlAmt = null;
   

   /**
    * Constructs the GIAInvestmentListInquiryView object.
    * 
    */
   public GIAInvestmentListInquiryView()
   {
      super ( new GIAInvestmentListInquiryRequest() );
   }

   /**
    * Constructs the GIAInvestmentListInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public GIAInvestmentListInquiryView( String hostEncoding )
   {
      super ( new GIAInvestmentListInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the GIAInvestmentListInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The GIAInvestmentListInquiryRequest object.
    */
   public final GIAInvestmentListInquiryRequest getRequest()
   {
      return (GIAInvestmentListInquiryRequest)getIFastRequest();
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
    * Gets the IntInvestUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntInvestUUID or null.
    */
   public final String getIntInvestUUID( int index )
   {
      return _IntInvestUUID[index];
   }
    
   /**
    * Gets the IntInvestUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntInvestUUID or the specified default value.
    */
   public final String getIntInvestUUID( int index, String defaultValue )
   {
      return _IntInvestUUID[index] == null ? defaultValue : _IntInvestUUID[index];
   }
    
   /**
    * Gets the array of IntInvestUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntInvestUUID values.
    */
   public final String[] getIntInvestUUIDArray()
   {
      return _IntInvestUUID;
   }
    
   /**
    * Gets the Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund or null.
    */
   public final String getFund( int index )
   {
      return _Fund[index];
   }
    
   /**
    * Gets the Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund or the specified default value.
    */
   public final String getFund( int index, String defaultValue )
   {
      return _Fund[index] == null ? defaultValue : _Fund[index];
   }
    
   /**
    * Gets the array of Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund values.
    */
   public final String[] getFundArray()
   {
      return _Fund;
   }
    
   /**
    * Gets the Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class or null.
    */
   public final String getClass( int index )
   {
      return _Class[index];
   }
    
   /**
    * Gets the Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class or the specified default value.
    */
   public final String getClass( int index, String defaultValue )
   {
      return _Class[index] == null ? defaultValue : _Class[index];
   }
    
   /**
    * Gets the array of Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class values.
    */
   public final String[] getClassArray()
   {
      return _Class;
   }
    
   /**
    * Gets the TransNum field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransNum or null.
    */
   public final Integer getTransNum( int index )
   {
      return _TransNum[index];
   }
    
   /**
    * Gets the TransNum field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransNum or the specified default value.
    */
   public final int getTransNum( int index, int defaultValue )
   {
      return _TransNum[index] == null ? defaultValue : _TransNum[index].intValue();
   }
    
   /**
    * Gets the array of TransNum fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransNum values.
    */
   public final Integer[] getTransNumArray()
   {
      return _TransNum;
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
    * Gets the InvestmentNo field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the InvestmentNo or null.
    */
   public final String getInvestmentNo( int index )
   {
      return _InvestmentNo[index];
   }
    
   /**
    * Gets the InvestmentNo field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InvestmentNo or the specified default value.
    */
   public final String getInvestmentNo( int index, String defaultValue )
   {
      return _InvestmentNo[index] == null ? defaultValue : _InvestmentNo[index];
   }
    
   /**
    * Gets the array of InvestmentNo fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of InvestmentNo values.
    */
   public final String[] getInvestmentNoArray()
   {
      return _InvestmentNo;
   }
    
   /**
    * Gets the InvestStatus field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the InvestStatus or null.
    */
   public final String getInvestStatus( int index )
   {
      return _InvestStatus[index];
   }
    
   /**
    * Gets the InvestStatus field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InvestStatus or the specified default value.
    */
   public final String getInvestStatus( int index, String defaultValue )
   {
      return _InvestStatus[index] == null ? defaultValue : _InvestStatus[index];
   }
    
   /**
    * Gets the array of InvestStatus fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of InvestStatus values.
    */
   public final String[] getInvestStatusArray()
   {
      return _InvestStatus;
   }
    
   /**
    * Gets the IntCalcMthd field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntCalcMthd or null.
    */
   public final String getIntCalcMthd( int index )
   {
      return _IntCalcMthd[index];
   }
    
   /**
    * Gets the IntCalcMthd field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntCalcMthd or the specified default value.
    */
   public final String getIntCalcMthd( int index, String defaultValue )
   {
      return _IntCalcMthd[index] == null ? defaultValue : _IntCalcMthd[index];
   }
    
   /**
    * Gets the array of IntCalcMthd fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntCalcMthd values.
    */
   public final String[] getIntCalcMthdArray()
   {
      return _IntCalcMthd;
   }
    
   /**
    * Gets the IntInvestType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntInvestType or null.
    */
   public final String getIntInvestType( int index )
   {
      return _IntInvestType[index];
   }
    
   /**
    * Gets the IntInvestType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntInvestType or the specified default value.
    */
   public final String getIntInvestType( int index, String defaultValue )
   {
      return _IntInvestType[index] == null ? defaultValue : _IntInvestType[index];
   }
    
   /**
    * Gets the array of IntInvestType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntInvestType values.
    */
   public final String[] getIntInvestTypeArray()
   {
      return _IntInvestType;
   }
    
   /**
    * Gets the InvestTerm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the InvestTerm or null.
    */
   public final Integer getInvestTerm( int index )
   {
      return _InvestTerm[index];
   }
    
   /**
    * Gets the InvestTerm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InvestTerm or the specified default value.
    */
   public final int getInvestTerm( int index, int defaultValue )
   {
      return _InvestTerm[index] == null ? defaultValue : _InvestTerm[index].intValue();
   }
    
   /**
    * Gets the array of InvestTerm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of InvestTerm values.
    */
   public final Integer[] getInvestTermArray()
   {
      return _InvestTerm;
   }
    
   /**
    * Gets the IntRate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntRate or null.
    */
   public final String getIntRate( int index )
   {
      return _IntRate[index];
   }
    
   /**
    * Gets the IntRate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntRate or the specified default value.
    */
   public final String getIntRate( int index, String defaultValue )
   {
      return _IntRate[index] == null ? defaultValue : _IntRate[index];
   }
    
   /**
    * Gets the array of IntRate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntRate values.
    */
   public final String[] getIntRateArray()
   {
      return _IntRate;
   }
    
   /**
    * Gets the DepositDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DepositDate or null.
    */
   public final Date getDepositDate( int index )
   {
      return _DepositDate[index];
   }
    
   /**
    * Gets the DepositDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DepositDate or the specified default value.
    */
   public final Date getDepositDate( int index, Date defaultValue )
   {
      return _DepositDate[index] == null ? defaultValue : _DepositDate[index];
   }
    
   /**
    * Gets the array of DepositDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DepositDate values.
    */
   public final Date[] getDepositDateArray()
   {
      return _DepositDate;
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
    * Gets the GIAmount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GIAmount or null.
    */
   public final String getGIAmount( int index )
   {
      return _GIAmount[index];
   }
    
   /**
    * Gets the GIAmount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GIAmount or the specified default value.
    */
   public final String getGIAmount( int index, String defaultValue )
   {
      return _GIAmount[index] == null ? defaultValue : _GIAmount[index];
   }
    
   /**
    * Gets the array of GIAmount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GIAmount values.
    */
   public final String[] getGIAmountArray()
   {
      return _GIAmount;
   }
    
   /**
    * Gets the IntCredFreq field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntCredFreq or null.
    */
   public final String getIntCredFreq( int index )
   {
      return _IntCredFreq[index];
   }
    
   /**
    * Gets the IntCredFreq field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntCredFreq or the specified default value.
    */
   public final String getIntCredFreq( int index, String defaultValue )
   {
      return _IntCredFreq[index] == null ? defaultValue : _IntCredFreq[index];
   }
    
   /**
    * Gets the array of IntCredFreq fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntCredFreq values.
    */
   public final String[] getIntCredFreqArray()
   {
      return _IntCredFreq;
   }
    
   /**
    * Gets the CurrentMKV field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CurrentMKV or null.
    */
   public final String getCurrentMKV( int index )
   {
      return _CurrentMKV[index];
   }
    
   /**
    * Gets the CurrentMKV field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CurrentMKV or the specified default value.
    */
   public final String getCurrentMKV( int index, String defaultValue )
   {
      return _CurrentMKV[index] == null ? defaultValue : _CurrentMKV[index];
   }
    
   /**
    * Gets the array of CurrentMKV fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CurrentMKV values.
    */
   public final String[] getCurrentMKVArray()
   {
      return _CurrentMKV;
   }
    
   /**
    * Gets the LastIntCredDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LastIntCredDate or null.
    */
   public final Date getLastIntCredDate( int index )
   {
      return _LastIntCredDate[index];
   }
    
   /**
    * Gets the LastIntCredDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LastIntCredDate or the specified default value.
    */
   public final Date getLastIntCredDate( int index, Date defaultValue )
   {
      return _LastIntCredDate[index] == null ? defaultValue : _LastIntCredDate[index];
   }
    
   /**
    * Gets the array of LastIntCredDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LastIntCredDate values.
    */
   public final Date[] getLastIntCredDateArray()
   {
      return _LastIntCredDate;
   }
    
   /**
    * Gets the IntAccruedToDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntAccruedToDate or null.
    */
   public final String getIntAccruedToDate( int index )
   {
      return _IntAccruedToDate[index];
   }
    
   /**
    * Gets the IntAccruedToDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntAccruedToDate or the specified default value.
    */
   public final String getIntAccruedToDate( int index, String defaultValue )
   {
      return _IntAccruedToDate[index] == null ? defaultValue : _IntAccruedToDate[index];
   }
    
   /**
    * Gets the array of IntAccruedToDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntAccruedToDate values.
    */
   public final String[] getIntAccruedToDateArray()
   {
      return _IntAccruedToDate;
   }
    
   /**
    * Gets the Moddate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Moddate or null.
    */
   public final Date getModdate( int index )
   {
      return _Moddate[index];
   }
    
   /**
    * Gets the Moddate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Moddate or the specified default value.
    */
   public final Date getModdate( int index, Date defaultValue )
   {
      return _Moddate[index] == null ? defaultValue : _Moddate[index];
   }
    
   /**
    * Gets the array of Moddate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Moddate values.
    */
   public final Date[] getModdateArray()
   {
      return _Moddate;
   }
    
   /**
    * Gets the Moduser field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Moduser or null.
    */
   public final String getModuser( int index )
   {
      return _Moduser[index];
   }
    
   /**
    * Gets the Moduser field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Moduser or the specified default value.
    */
   public final String getModuser( int index, String defaultValue )
   {
      return _Moduser[index] == null ? defaultValue : _Moduser[index];
   }
    
   /**
    * Gets the array of Moduser fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Moduser values.
    */
   public final String[] getModuserArray()
   {
      return _Moduser;
   }
    
   /**
    * Gets the Username field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Username or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the Username field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Username or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of Username fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Username values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
   }
    
   /**
    * Gets the Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Version or null.
    */
   public final Integer getVersion( int index )
   {
      return _Version[index];
   }
    
   /**
    * Gets the Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version or the specified default value.
    */
   public final int getVersion( int index, int defaultValue )
   {
      return _Version[index] == null ? defaultValue : _Version[index].intValue();
   }
    
   /**
    * Gets the array of Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version values.
    */
   public final Integer[] getVersionArray()
   {
      return _Version;
   }
    
   /**
    * Gets the LotId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LotId or null.
    */
   public final String getLotId( int index )
   {
      return _LotId[index];
   }
    
   /**
    * Gets the LotId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LotId or the specified default value.
    */
   public final String getLotId( int index, String defaultValue )
   {
      return _LotId[index] == null ? defaultValue : _LotId[index];
   }
    
   /**
    * Gets the array of LotId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LotId values.
    */
   public final String[] getLotIdArray()
   {
      return _LotId;
   }
    
   /**
    * Gets the IntInvestId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntInvestId or null.
    */
   public final String getIntInvestId( int index )
   {
      return _IntInvestId[index];
   }
    
   /**
    * Gets the IntInvestId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntInvestId or the specified default value.
    */
   public final String getIntInvestId( int index, String defaultValue )
   {
      return _IntInvestId[index] == null ? defaultValue : _IntInvestId[index];
   }
    
   /**
    * Gets the array of IntInvestId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntInvestId values.
    */
   public final String[] getIntInvestIdArray()
   {
      return _IntInvestId;
   }
    
   /**
    * Gets the PrincipalAmt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PrincipalAmt or null.
    */
   public final String getPrincipalAmt( int index )
   {
      return _PrincipalAmt[index];
   }
    
   /**
    * Gets the PrincipalAmt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PrincipalAmt or the specified default value.
    */
   public final String getPrincipalAmt( int index, String defaultValue )
   {
      return _PrincipalAmt[index] == null ? defaultValue : _PrincipalAmt[index];
   }
    
   /**
    * Gets the array of PrincipalAmt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PrincipalAmt values.
    */
   public final String[] getPrincipalAmtArray()
   {
      return _PrincipalAmt;
   }
    
   /**
    * Gets the MarketValue field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the MarketValue or null.
    */
   public final String getMarketValue( int index )
   {
      return _MarketValue[index];
   }
    
   /**
    * Gets the MarketValue field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MarketValue or the specified default value.
    */
   public final String getMarketValue( int index, String defaultValue )
   {
      return _MarketValue[index] == null ? defaultValue : _MarketValue[index];
   }
    
   /**
    * Gets the array of MarketValue fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of MarketValue values.
    */
   public final String[] getMarketValueArray()
   {
      return _MarketValue;
   }
    
   /**
    * Gets the ValueAtMaturity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ValueAtMaturity or null.
    */
   public final String getValueAtMaturity( int index )
   {
      return _ValueAtMaturity[index];
   }
    
   /**
    * Gets the ValueAtMaturity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ValueAtMaturity or the specified default value.
    */
   public final String getValueAtMaturity( int index, String defaultValue )
   {
      return _ValueAtMaturity[index] == null ? defaultValue : _ValueAtMaturity[index];
   }
    
   /**
    * Gets the array of ValueAtMaturity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ValueAtMaturity values.
    */
   public final String[] getValueAtMaturityArray()
   {
      return _ValueAtMaturity;
   }
    
   /**
    * Gets the SelInvAmtType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SelInvAmtType or null.
    */
   public final String getSelInvAmtType( int index )
   {
      return _SelInvAmtType[index];
   }
    
   /**
    * Gets the SelInvAmtType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SelInvAmtType or the specified default value.
    */
   public final String getSelInvAmtType( int index, String defaultValue )
   {
      return _SelInvAmtType[index] == null ? defaultValue : _SelInvAmtType[index];
   }
    
   /**
    * Gets the array of SelInvAmtType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SelInvAmtType values.
    */
   public final String[] getSelInvAmtTypeArray()
   {
      return _SelInvAmtType;
   }
    
   /**
    * Gets the SelInvAmount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SelInvAmount or null.
    */
   public final String getSelInvAmount( int index )
   {
      return _SelInvAmount[index];
   }
    
   /**
    * Gets the SelInvAmount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SelInvAmount or the specified default value.
    */
   public final String getSelInvAmount( int index, String defaultValue )
   {
      return _SelInvAmount[index] == null ? defaultValue : _SelInvAmount[index];
   }
    
   /**
    * Gets the array of SelInvAmount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SelInvAmount values.
    */
   public final String[] getSelInvAmountArray()
   {
      return _SelInvAmount;
   }
    
   /**
    * Gets the PrincipalRedeem field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PrincipalRedeem or null.
    */
   public final String getPrincipalRedeem( int index )
   {
      return _PrincipalRedeem[index];
   }
    
   /**
    * Gets the PrincipalRedeem field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PrincipalRedeem or the specified default value.
    */
   public final String getPrincipalRedeem( int index, String defaultValue )
   {
      return _PrincipalRedeem[index] == null ? defaultValue : _PrincipalRedeem[index];
   }
    
   /**
    * Gets the array of PrincipalRedeem fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PrincipalRedeem values.
    */
   public final String[] getPrincipalRedeemArray()
   {
      return _PrincipalRedeem;
   }
    
   /**
    * Gets the AccruedInt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AccruedInt or null.
    */
   public final String getAccruedInt( int index )
   {
      return _AccruedInt[index];
   }
    
   /**
    * Gets the AccruedInt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AccruedInt or the specified default value.
    */
   public final String getAccruedInt( int index, String defaultValue )
   {
      return _AccruedInt[index] == null ? defaultValue : _AccruedInt[index];
   }
    
   /**
    * Gets the array of AccruedInt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AccruedInt values.
    */
   public final String[] getAccruedIntArray()
   {
      return _AccruedInt;
   }
    
   /**
    * Gets the AdminFee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AdminFee or null.
    */
   public final String getAdminFee( int index )
   {
      return _AdminFee[index];
   }
    
   /**
    * Gets the AdminFee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AdminFee or the specified default value.
    */
   public final String getAdminFee( int index, String defaultValue )
   {
      return _AdminFee[index] == null ? defaultValue : _AdminFee[index];
   }
    
   /**
    * Gets the array of AdminFee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AdminFee values.
    */
   public final String[] getAdminFeeArray()
   {
      return _AdminFee;
   }
    
   /**
    * Gets the MVA field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the MVA or null.
    */
   public final String getMVA( int index )
   {
      return _MVA[index];
   }
    
   /**
    * Gets the MVA field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MVA or the specified default value.
    */
   public final String getMVA( int index, String defaultValue )
   {
      return _MVA[index] == null ? defaultValue : _MVA[index];
   }
    
   /**
    * Gets the array of MVA fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of MVA values.
    */
   public final String[] getMVAArray()
   {
      return _MVA;
   }
    
   /**
    * Gets the AmountNet field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AmountNet or null.
    */
   public final String getAmountNet( int index )
   {
      return _AmountNet[index];
   }
    
   /**
    * Gets the AmountNet field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AmountNet or the specified default value.
    */
   public final String getAmountNet( int index, String defaultValue )
   {
      return _AmountNet[index] == null ? defaultValue : _AmountNet[index];
   }
    
   /**
    * Gets the array of AmountNet fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AmountNet values.
    */
   public final String[] getAmountNetArray()
   {
      return _AmountNet;
   }
    
   /**
    * Gets the InvSummId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the InvSummId or null.
    */
   public final Integer getInvSummId( int index )
   {
      return _InvSummId[index];
   }
    
   /**
    * Gets the InvSummId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InvSummId or the specified default value.
    */
   public final int getInvSummId( int index, int defaultValue )
   {
      return _InvSummId[index] == null ? defaultValue : _InvSummId[index].intValue();
   }
    
   /**
    * Gets the array of InvSummId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of InvSummId values.
    */
   public final Integer[] getInvSummIdArray()
   {
      return _InvSummId;
   }
    
   /**
    * Gets the IsSelected field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IsSelected or null.
    */
   public final Boolean getIsSelected( int index )
   {
      return _IsSelected[index];
   }
    
   /**
    * Gets the IsSelected field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IsSelected or the specified default value.
    */
   public final boolean getIsSelected( int index, boolean defaultValue )
   {
      return _IsSelected[index] == null ? defaultValue : _IsSelected[index].booleanValue();
   }
    
   /**
    * Gets the array of IsSelected fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IsSelected values.
    */
   public final Boolean[] getIsSelectedArray()
   {
      return _IsSelected;
   }
    
   /**
    * Gets the IntRateType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntRateType or null.
    */
   public final String getIntRateType( int index )
   {
      return _IntRateType[index];
   }
    
   /**
    * Gets the IntRateType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntRateType or the specified default value.
    */
   public final String getIntRateType( int index, String defaultValue )
   {
      return _IntRateType[index] == null ? defaultValue : _IntRateType[index];
   }
    
   /**
    * Gets the array of IntRateType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntRateType values.
    */
   public final String[] getIntRateTypeArray()
   {
      return _IntRateType;
   }
    
   /**
    * Gets the Additional Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Additional Amount or null.
    */
   public final String getAddlAmt( int index )
   {
      return _AddlAmt[index];
   }
    
   /**
    * Gets the Additional Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Additional Amount or the specified default value.
    */
   public final String getAddlAmt( int index, String defaultValue )
   {
      return _AddlAmt[index] == null ? defaultValue : _AddlAmt[index];
   }
    
   /**
    * Gets the array of Additional Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Additional Amount values.
    */
   public final String[] getAddlAmtArray()
   {
      return _AddlAmt;
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
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _IntInvestUUID = resizeArray( _IntInvestUUID, _RepeatCount );
      _Fund = resizeArray( _Fund, _RepeatCount );
      _Class = resizeArray( _Class, _RepeatCount );
      _TransNum = resizeArray( _TransNum, _RepeatCount );
      _TransId = resizeArray( _TransId, _RepeatCount );
      _InvestmentNo = resizeArray( _InvestmentNo, _RepeatCount );
      _InvestStatus = resizeArray( _InvestStatus, _RepeatCount );
      _IntCalcMthd = resizeArray( _IntCalcMthd, _RepeatCount );
      _IntInvestType = resizeArray( _IntInvestType, _RepeatCount );
      _InvestTerm = resizeArray( _InvestTerm, _RepeatCount );
      _IntRate = resizeArray( _IntRate, _RepeatCount );
      _DepositDate = resizeArray( _DepositDate, _RepeatCount );
      _MaturityDate = resizeArray( _MaturityDate, _RepeatCount );
      _GIAmount = resizeArray( _GIAmount, _RepeatCount );
      _IntCredFreq = resizeArray( _IntCredFreq, _RepeatCount );
      _CurrentMKV = resizeArray( _CurrentMKV, _RepeatCount );
      _LastIntCredDate = resizeArray( _LastIntCredDate, _RepeatCount );
      _IntAccruedToDate = resizeArray( _IntAccruedToDate, _RepeatCount );
      _Moddate = resizeArray( _Moddate, _RepeatCount );
      _Moduser = resizeArray( _Moduser, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _Version = resizeArray( _Version, _RepeatCount );
      _LotId = resizeArray( _LotId, _RepeatCount );
      _IntInvestId = resizeArray( _IntInvestId, _RepeatCount );
      _PrincipalAmt = resizeArray( _PrincipalAmt, _RepeatCount );
      _MarketValue = resizeArray( _MarketValue, _RepeatCount );
      _ValueAtMaturity = resizeArray( _ValueAtMaturity, _RepeatCount );
      _SelInvAmtType = resizeArray( _SelInvAmtType, _RepeatCount );
      _SelInvAmount = resizeArray( _SelInvAmount, _RepeatCount );
      _PrincipalRedeem = resizeArray( _PrincipalRedeem, _RepeatCount );
      _AccruedInt = resizeArray( _AccruedInt, _RepeatCount );
      _AdminFee = resizeArray( _AdminFee, _RepeatCount );
      _MVA = resizeArray( _MVA, _RepeatCount );
      _AmountNet = resizeArray( _AmountNet, _RepeatCount );
      _InvSummId = resizeArray( _InvSummId, _RepeatCount );
      _IsSelected = resizeArray( _IsSelected, _RepeatCount );
      _IntRateType = resizeArray( _IntRateType, _RepeatCount );
      _AddlAmt = resizeArray( _AddlAmt, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _IntInvestUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Fund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Class[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TransId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InvestmentNo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InvestStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntCalcMthd[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntInvestType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InvestTerm[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _IntRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DepositDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _MaturityDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _GIAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntCredFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CurrentMKV[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastIntCredDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _IntAccruedToDate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Moddate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Moduser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Version[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _LotId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntInvestId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PrincipalAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MarketValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ValueAtMaturity[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SelInvAmtType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SelInvAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PrincipalRedeem[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccruedInt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AdminFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MVA[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountNet[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InvSummId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _IsSelected[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _IntRateType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddlAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
