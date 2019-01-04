
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Aggregated  Orders Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AggrOrdInq.doc">AggrOrdInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AggrOrdInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Aggregation Option member array.
    */
   private String[] _AggrOption = null;
   
   /**
    * Omnibus Id member array.
    */
   private String[] _rxOmnibusId = null;
   
   /**
    * Fund Broker member array.
    */
   private String[] _rxFundBroker = null;
   
   /**
    * FundCode member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Transaction Type member array.
    */
   private String[] _TransType = null;
   
   /**
    * Group Code member array.
    */
   private String[] _GroupCode = null;
   
   /**
    * Amount member array.
    */
   private String[] _Amount = null;
   
   /**
    * Amount  Type member array.
    */
   private String[] _AmountType = null;
   
   /**
    * Trade Date member array.
    */
   private Date[] _TradeDate = null;
   
   /**
    * Broker Settlement Date member array.
    */
   private Date[] _BrkSettlDate = null;
   
   /**
    * Broker Settlement Amount in Units member array.
    */
   private String[] _BrkSettlAmtUnits = null;
   
   /**
    * Broker Settlement PUd member array.
    */
   private String[] _BrkSettlPUD = null;
   
   /**
    * AFT Benefit member array.
    */
   private String[] _AFTBenefit = null;
   
   /**
    * Price member array.
    */
   private String[] _Price = null;
   
   /**
    * Price Type member array.
    */
   private String[] _PriceType = null;
   
   /**
    * Commission Rate member array.
    */
   private String[] _Commission = null;
   
   /**
    * External Charge member array.
    */
   private String[] _ExternCharge = null;
   
   /**
    * Rebate Rate member array.
    */
   private String[] _RebateRate = null;
   
   /**
    * Order Status member array.
    */
   private String[] _rxOrdStatus = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Mod User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Mod Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Calc NAV member array.
    */
   private String[] _NAV = null;
   
   /**
    * Calc Offer Price member array.
    */
   private String[] _OfferPrice = null;
   
   /**
    * Delivery To member array.
    */
   private String[] _DeliveryTo = null;
   
   /**
    * For Account member array.
    */
   private String[] _ForAccount = null;
   
   /**
    * In Favour Of member array.
    */
   private String[] _InFavourOf = null;
   
   /**
    * Settlement Instruction Code member array.
    */
   private String[] _SettlInstrCode = null;
   
   /**
    * Settlement Account Number member array.
    */
   private String[] _SettlAcctNum = null;
   
   /**
    * Settlement Location Code member array.
    */
   private String[] _SettlLocCode = null;
   
   /**
    * Process Time member array.
    */
   private String[] _ProcessTime = null;
   
   /**
    * Remarks member array.
    */
   private String[] _Remarks = null;
   
   /**
    * Routing Ref Num member array.
    */
   private String[] _rxRoutRefNum = null;
   
   /**
    * Routing Type member array.
    */
   private String[] _RoutingType = null;
   
   /**
    * Aggregated Order ID member array.
    */
   private Integer[] _AggrOrdId = null;
   
   /**
    * Aggregated Order Version member array.
    */
   private Integer[] _AggrOrdVer = null;
   
   /**
    * Clear Settlement Method member array.
    */
   private String[] _ClrSettlMethod = null;
   
   /**
    * Fund Broker Name member array.
    */
   private String[] _FundBrokerName = null;
   
   /**
    * Fund Name member array.
    */
   private String[] _FundName = null;
   
   /**
    * Reason Code member array.
    */
   private String[] _ReasonCode = null;
   
   /**
    * Fund ID Type member array.
    */
   private String[] _rxFundIdType = null;
   
   /**
    * Fund ID Value member array.
    */
   private String[] _rxFundIdValue = null;
   
   /**
    * Security Recon File member array.
    */
   private String[] _SecReconFile = null;
   
   /**
    * Flag indicating if there is 1 processed trade member array.
    */
   private Boolean[] _ProcessedTrade = null;
   
   /**
    * AggrDate member array.
    */
   private Date[] _AggrDate = null;
   
   /**
    * AggrTime member array.
    */
   private String[] _AggrTime = null;
   
   /**
    * CashMsgType member array.
    */
   private String[] _CashMsgType = null;
   
   /**
    * IntermediaryBank member array.
    */
   private String[] _IntermediaryBank = null;
   
   /**
    * ReceivingBank member array.
    */
   private String[] _ReceivingBank = null;
   
   /**
    * Beneficiary member array.
    */
   private String[] _Beneficiary = null;
   
   /**
    * SpecialInstructions member array.
    */
   private String[] _SpecialInstructions = null;
   
   /**
    * InternalSettlementAccount member array.
    */
   private String[] _InternalSettlementAccount = null;
   
   /**
    * LastModStatus member array.
    */
   private String[] _LastModStatus = null;
   
   /**
    * CancelReqUser member array.
    */
   private String[] _CancelReqUser = null;
   

   /**
    * Constructs the AggrOrdInqView object.
    * 
    */
   public AggrOrdInqView()
   {
      super ( new AggrOrdInqRequest() );
   }

   /**
    * Constructs the AggrOrdInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AggrOrdInqView( String hostEncoding )
   {
      super ( new AggrOrdInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AggrOrdInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AggrOrdInqRequest object.
    */
   public final AggrOrdInqRequest getRequest()
   {
      return (AggrOrdInqRequest)getIFastRequest();
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
    * Gets the Aggregation Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Aggregation Option or null.
    */
   public final String getAggrOption( int index )
   {
      return _AggrOption[index];
   }
    
   /**
    * Gets the Aggregation Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Aggregation Option or the specified default value.
    */
   public final String getAggrOption( int index, String defaultValue )
   {
      return _AggrOption[index] == null ? defaultValue : _AggrOption[index];
   }
    
   /**
    * Gets the array of Aggregation Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Aggregation Option values.
    */
   public final String[] getAggrOptionArray()
   {
      return _AggrOption;
   }
    
   /**
    * Gets the Omnibus Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Omnibus Id or null.
    */
   public final String getrxOmnibusId( int index )
   {
      return _rxOmnibusId[index];
   }
    
   /**
    * Gets the Omnibus Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Omnibus Id or the specified default value.
    */
   public final String getrxOmnibusId( int index, String defaultValue )
   {
      return _rxOmnibusId[index] == null ? defaultValue : _rxOmnibusId[index];
   }
    
   /**
    * Gets the array of Omnibus Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Omnibus Id values.
    */
   public final String[] getrxOmnibusIdArray()
   {
      return _rxOmnibusId;
   }
    
   /**
    * Gets the Fund Broker field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker or null.
    */
   public final String getrxFundBroker( int index )
   {
      return _rxFundBroker[index];
   }
    
   /**
    * Gets the Fund Broker field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker or the specified default value.
    */
   public final String getrxFundBroker( int index, String defaultValue )
   {
      return _rxFundBroker[index] == null ? defaultValue : _rxFundBroker[index];
   }
    
   /**
    * Gets the array of Fund Broker fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker values.
    */
   public final String[] getrxFundBrokerArray()
   {
      return _rxFundBroker;
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
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
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
    * Gets the Group Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Group Code or null.
    */
   public final String getGroupCode( int index )
   {
      return _GroupCode[index];
   }
    
   /**
    * Gets the Group Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Group Code or the specified default value.
    */
   public final String getGroupCode( int index, String defaultValue )
   {
      return _GroupCode[index] == null ? defaultValue : _GroupCode[index];
   }
    
   /**
    * Gets the array of Group Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Group Code values.
    */
   public final String[] getGroupCodeArray()
   {
      return _GroupCode;
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount or null.
    */
   public final String getAmount( int index )
   {
      return _Amount[index];
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount or the specified default value.
    */
   public final String getAmount( int index, String defaultValue )
   {
      return _Amount[index] == null ? defaultValue : _Amount[index];
   }
    
   /**
    * Gets the array of Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount values.
    */
   public final String[] getAmountArray()
   {
      return _Amount;
   }
    
   /**
    * Gets the Amount  Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount  Type or null.
    */
   public final String getAmountType( int index )
   {
      return _AmountType[index];
   }
    
   /**
    * Gets the Amount  Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount  Type or the specified default value.
    */
   public final String getAmountType( int index, String defaultValue )
   {
      return _AmountType[index] == null ? defaultValue : _AmountType[index];
   }
    
   /**
    * Gets the array of Amount  Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount  Type values.
    */
   public final String[] getAmountTypeArray()
   {
      return _AmountType;
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
    * Gets the Broker Settlement Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Settlement Date or null.
    */
   public final Date getBrkSettlDate( int index )
   {
      return _BrkSettlDate[index];
   }
    
   /**
    * Gets the Broker Settlement Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Settlement Date or the specified default value.
    */
   public final Date getBrkSettlDate( int index, Date defaultValue )
   {
      return _BrkSettlDate[index] == null ? defaultValue : _BrkSettlDate[index];
   }
    
   /**
    * Gets the array of Broker Settlement Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Settlement Date values.
    */
   public final Date[] getBrkSettlDateArray()
   {
      return _BrkSettlDate;
   }
    
   /**
    * Gets the Broker Settlement Amount in Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Settlement Amount in Units or null.
    */
   public final String getBrkSettlAmtUnits( int index )
   {
      return _BrkSettlAmtUnits[index];
   }
    
   /**
    * Gets the Broker Settlement Amount in Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Settlement Amount in Units or the specified default value.
    */
   public final String getBrkSettlAmtUnits( int index, String defaultValue )
   {
      return _BrkSettlAmtUnits[index] == null ? defaultValue : _BrkSettlAmtUnits[index];
   }
    
   /**
    * Gets the array of Broker Settlement Amount in Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Settlement Amount in Units values.
    */
   public final String[] getBrkSettlAmtUnitsArray()
   {
      return _BrkSettlAmtUnits;
   }
    
   /**
    * Gets the Broker Settlement PUd field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Settlement PUd or null.
    */
   public final String getBrkSettlPUD( int index )
   {
      return _BrkSettlPUD[index];
   }
    
   /**
    * Gets the Broker Settlement PUd field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Settlement PUd or the specified default value.
    */
   public final String getBrkSettlPUD( int index, String defaultValue )
   {
      return _BrkSettlPUD[index] == null ? defaultValue : _BrkSettlPUD[index];
   }
    
   /**
    * Gets the array of Broker Settlement PUd fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Settlement PUd values.
    */
   public final String[] getBrkSettlPUDArray()
   {
      return _BrkSettlPUD;
   }
    
   /**
    * Gets the AFT Benefit field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AFT Benefit or null.
    */
   public final String getAFTBenefit( int index )
   {
      return _AFTBenefit[index];
   }
    
   /**
    * Gets the AFT Benefit field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AFT Benefit or the specified default value.
    */
   public final String getAFTBenefit( int index, String defaultValue )
   {
      return _AFTBenefit[index] == null ? defaultValue : _AFTBenefit[index];
   }
    
   /**
    * Gets the array of AFT Benefit fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AFT Benefit values.
    */
   public final String[] getAFTBenefitArray()
   {
      return _AFTBenefit;
   }
    
   /**
    * Gets the Price field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Price or null.
    */
   public final String getPrice( int index )
   {
      return _Price[index];
   }
    
   /**
    * Gets the Price field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Price or the specified default value.
    */
   public final String getPrice( int index, String defaultValue )
   {
      return _Price[index] == null ? defaultValue : _Price[index];
   }
    
   /**
    * Gets the array of Price fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Price values.
    */
   public final String[] getPriceArray()
   {
      return _Price;
   }
    
   /**
    * Gets the Price Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Price Type or null.
    */
   public final String getPriceType( int index )
   {
      return _PriceType[index];
   }
    
   /**
    * Gets the Price Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Price Type or the specified default value.
    */
   public final String getPriceType( int index, String defaultValue )
   {
      return _PriceType[index] == null ? defaultValue : _PriceType[index];
   }
    
   /**
    * Gets the array of Price Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Price Type values.
    */
   public final String[] getPriceTypeArray()
   {
      return _PriceType;
   }
    
   /**
    * Gets the Commission Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission Rate or null.
    */
   public final String getCommission( int index )
   {
      return _Commission[index];
   }
    
   /**
    * Gets the Commission Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Rate or the specified default value.
    */
   public final String getCommission( int index, String defaultValue )
   {
      return _Commission[index] == null ? defaultValue : _Commission[index];
   }
    
   /**
    * Gets the array of Commission Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Rate values.
    */
   public final String[] getCommissionArray()
   {
      return _Commission;
   }
    
   /**
    * Gets the External Charge field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the External Charge or null.
    */
   public final String getExternCharge( int index )
   {
      return _ExternCharge[index];
   }
    
   /**
    * Gets the External Charge field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the External Charge or the specified default value.
    */
   public final String getExternCharge( int index, String defaultValue )
   {
      return _ExternCharge[index] == null ? defaultValue : _ExternCharge[index];
   }
    
   /**
    * Gets the array of External Charge fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of External Charge values.
    */
   public final String[] getExternChargeArray()
   {
      return _ExternCharge;
   }
    
   /**
    * Gets the Rebate Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rebate Rate or null.
    */
   public final String getRebateRate( int index )
   {
      return _RebateRate[index];
   }
    
   /**
    * Gets the Rebate Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rebate Rate or the specified default value.
    */
   public final String getRebateRate( int index, String defaultValue )
   {
      return _RebateRate[index] == null ? defaultValue : _RebateRate[index];
   }
    
   /**
    * Gets the array of Rebate Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rebate Rate values.
    */
   public final String[] getRebateRateArray()
   {
      return _RebateRate;
   }
    
   /**
    * Gets the Order Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Order Status or null.
    */
   public final String getrxOrdStatus( int index )
   {
      return _rxOrdStatus[index];
   }
    
   /**
    * Gets the Order Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Order Status or the specified default value.
    */
   public final String getrxOrdStatus( int index, String defaultValue )
   {
      return _rxOrdStatus[index] == null ? defaultValue : _rxOrdStatus[index];
   }
    
   /**
    * Gets the array of Order Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Order Status values.
    */
   public final String[] getrxOrdStatusArray()
   {
      return _rxOrdStatus;
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Name or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Name or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of User Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Name values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Date or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Date or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Date values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Mod User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Mod Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Mod Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Mod Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Calc NAV field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Calc NAV or null.
    */
   public final String getNAV( int index )
   {
      return _NAV[index];
   }
    
   /**
    * Gets the Calc NAV field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calc NAV or the specified default value.
    */
   public final String getNAV( int index, String defaultValue )
   {
      return _NAV[index] == null ? defaultValue : _NAV[index];
   }
    
   /**
    * Gets the array of Calc NAV fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Calc NAV values.
    */
   public final String[] getNAVArray()
   {
      return _NAV;
   }
    
   /**
    * Gets the Calc Offer Price field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Calc Offer Price or null.
    */
   public final String getOfferPrice( int index )
   {
      return _OfferPrice[index];
   }
    
   /**
    * Gets the Calc Offer Price field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calc Offer Price or the specified default value.
    */
   public final String getOfferPrice( int index, String defaultValue )
   {
      return _OfferPrice[index] == null ? defaultValue : _OfferPrice[index];
   }
    
   /**
    * Gets the array of Calc Offer Price fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Calc Offer Price values.
    */
   public final String[] getOfferPriceArray()
   {
      return _OfferPrice;
   }
    
   /**
    * Gets the Delivery To field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Delivery To or null.
    */
   public final String getDeliveryTo( int index )
   {
      return _DeliveryTo[index];
   }
    
   /**
    * Gets the Delivery To field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Delivery To or the specified default value.
    */
   public final String getDeliveryTo( int index, String defaultValue )
   {
      return _DeliveryTo[index] == null ? defaultValue : _DeliveryTo[index];
   }
    
   /**
    * Gets the array of Delivery To fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Delivery To values.
    */
   public final String[] getDeliveryToArray()
   {
      return _DeliveryTo;
   }
    
   /**
    * Gets the For Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the For Account or null.
    */
   public final String getForAccount( int index )
   {
      return _ForAccount[index];
   }
    
   /**
    * Gets the For Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the For Account or the specified default value.
    */
   public final String getForAccount( int index, String defaultValue )
   {
      return _ForAccount[index] == null ? defaultValue : _ForAccount[index];
   }
    
   /**
    * Gets the array of For Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of For Account values.
    */
   public final String[] getForAccountArray()
   {
      return _ForAccount;
   }
    
   /**
    * Gets the In Favour Of field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the In Favour Of or null.
    */
   public final String getInFavourOf( int index )
   {
      return _InFavourOf[index];
   }
    
   /**
    * Gets the In Favour Of field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the In Favour Of or the specified default value.
    */
   public final String getInFavourOf( int index, String defaultValue )
   {
      return _InFavourOf[index] == null ? defaultValue : _InFavourOf[index];
   }
    
   /**
    * Gets the array of In Favour Of fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of In Favour Of values.
    */
   public final String[] getInFavourOfArray()
   {
      return _InFavourOf;
   }
    
   /**
    * Gets the Settlement Instruction Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Instruction Code or null.
    */
   public final String getSettlInstrCode( int index )
   {
      return _SettlInstrCode[index];
   }
    
   /**
    * Gets the Settlement Instruction Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Instruction Code or the specified default value.
    */
   public final String getSettlInstrCode( int index, String defaultValue )
   {
      return _SettlInstrCode[index] == null ? defaultValue : _SettlInstrCode[index];
   }
    
   /**
    * Gets the array of Settlement Instruction Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Instruction Code values.
    */
   public final String[] getSettlInstrCodeArray()
   {
      return _SettlInstrCode;
   }
    
   /**
    * Gets the Settlement Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Account Number or null.
    */
   public final String getSettlAcctNum( int index )
   {
      return _SettlAcctNum[index];
   }
    
   /**
    * Gets the Settlement Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Account Number or the specified default value.
    */
   public final String getSettlAcctNum( int index, String defaultValue )
   {
      return _SettlAcctNum[index] == null ? defaultValue : _SettlAcctNum[index];
   }
    
   /**
    * Gets the array of Settlement Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Account Number values.
    */
   public final String[] getSettlAcctNumArray()
   {
      return _SettlAcctNum;
   }
    
   /**
    * Gets the Settlement Location Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Location Code or null.
    */
   public final String getSettlLocCode( int index )
   {
      return _SettlLocCode[index];
   }
    
   /**
    * Gets the Settlement Location Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Location Code or the specified default value.
    */
   public final String getSettlLocCode( int index, String defaultValue )
   {
      return _SettlLocCode[index] == null ? defaultValue : _SettlLocCode[index];
   }
    
   /**
    * Gets the array of Settlement Location Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Location Code values.
    */
   public final String[] getSettlLocCodeArray()
   {
      return _SettlLocCode;
   }
    
   /**
    * Gets the Process Time field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Time or null.
    */
   public final String getProcessTime( int index )
   {
      return _ProcessTime[index];
   }
    
   /**
    * Gets the Process Time field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Time or the specified default value.
    */
   public final String getProcessTime( int index, String defaultValue )
   {
      return _ProcessTime[index] == null ? defaultValue : _ProcessTime[index];
   }
    
   /**
    * Gets the array of Process Time fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Time values.
    */
   public final String[] getProcessTimeArray()
   {
      return _ProcessTime;
   }
    
   /**
    * Gets the Remarks field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks or null.
    */
   public final String getRemarks( int index )
   {
      return _Remarks[index];
   }
    
   /**
    * Gets the Remarks field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks or the specified default value.
    */
   public final String getRemarks( int index, String defaultValue )
   {
      return _Remarks[index] == null ? defaultValue : _Remarks[index];
   }
    
   /**
    * Gets the array of Remarks fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks values.
    */
   public final String[] getRemarksArray()
   {
      return _Remarks;
   }
    
   /**
    * Gets the Routing Ref Num field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Routing Ref Num or null.
    */
   public final String getrxRoutRefNum( int index )
   {
      return _rxRoutRefNum[index];
   }
    
   /**
    * Gets the Routing Ref Num field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Routing Ref Num or the specified default value.
    */
   public final String getrxRoutRefNum( int index, String defaultValue )
   {
      return _rxRoutRefNum[index] == null ? defaultValue : _rxRoutRefNum[index];
   }
    
   /**
    * Gets the array of Routing Ref Num fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Routing Ref Num values.
    */
   public final String[] getrxRoutRefNumArray()
   {
      return _rxRoutRefNum;
   }
    
   /**
    * Gets the Routing Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Routing Type or null.
    */
   public final String getRoutingType( int index )
   {
      return _RoutingType[index];
   }
    
   /**
    * Gets the Routing Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Routing Type or the specified default value.
    */
   public final String getRoutingType( int index, String defaultValue )
   {
      return _RoutingType[index] == null ? defaultValue : _RoutingType[index];
   }
    
   /**
    * Gets the array of Routing Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Routing Type values.
    */
   public final String[] getRoutingTypeArray()
   {
      return _RoutingType;
   }
    
   /**
    * Gets the Aggregated Order ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Aggregated Order ID or null.
    */
   public final Integer getAggrOrdId( int index )
   {
      return _AggrOrdId[index];
   }
    
   /**
    * Gets the Aggregated Order ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Aggregated Order ID or the specified default value.
    */
   public final int getAggrOrdId( int index, int defaultValue )
   {
      return _AggrOrdId[index] == null ? defaultValue : _AggrOrdId[index].intValue();
   }
    
   /**
    * Gets the array of Aggregated Order ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Aggregated Order ID values.
    */
   public final Integer[] getAggrOrdIdArray()
   {
      return _AggrOrdId;
   }
    
   /**
    * Gets the Aggregated Order Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Aggregated Order Version or null.
    */
   public final Integer getAggrOrdVer( int index )
   {
      return _AggrOrdVer[index];
   }
    
   /**
    * Gets the Aggregated Order Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Aggregated Order Version or the specified default value.
    */
   public final int getAggrOrdVer( int index, int defaultValue )
   {
      return _AggrOrdVer[index] == null ? defaultValue : _AggrOrdVer[index].intValue();
   }
    
   /**
    * Gets the array of Aggregated Order Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Aggregated Order Version values.
    */
   public final Integer[] getAggrOrdVerArray()
   {
      return _AggrOrdVer;
   }
    
   /**
    * Gets the Clear Settlement Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Clear Settlement Method or null.
    */
   public final String getClrSettlMethod( int index )
   {
      return _ClrSettlMethod[index];
   }
    
   /**
    * Gets the Clear Settlement Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Clear Settlement Method or the specified default value.
    */
   public final String getClrSettlMethod( int index, String defaultValue )
   {
      return _ClrSettlMethod[index] == null ? defaultValue : _ClrSettlMethod[index];
   }
    
   /**
    * Gets the array of Clear Settlement Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Clear Settlement Method values.
    */
   public final String[] getClrSettlMethodArray()
   {
      return _ClrSettlMethod;
   }
    
   /**
    * Gets the Fund Broker Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Name or null.
    */
   public final String getFundBrokerName( int index )
   {
      return _FundBrokerName[index];
   }
    
   /**
    * Gets the Fund Broker Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Name or the specified default value.
    */
   public final String getFundBrokerName( int index, String defaultValue )
   {
      return _FundBrokerName[index] == null ? defaultValue : _FundBrokerName[index];
   }
    
   /**
    * Gets the array of Fund Broker Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Name values.
    */
   public final String[] getFundBrokerNameArray()
   {
      return _FundBrokerName;
   }
    
   /**
    * Gets the Fund Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Name or null.
    */
   public final String getFundName( int index )
   {
      return _FundName[index];
   }
    
   /**
    * Gets the Fund Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Name or the specified default value.
    */
   public final String getFundName( int index, String defaultValue )
   {
      return _FundName[index] == null ? defaultValue : _FundName[index];
   }
    
   /**
    * Gets the array of Fund Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Name values.
    */
   public final String[] getFundNameArray()
   {
      return _FundName;
   }
    
   /**
    * Gets the Reason Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reason Code or null.
    */
   public final String getReasonCode( int index )
   {
      return _ReasonCode[index];
   }
    
   /**
    * Gets the Reason Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reason Code or the specified default value.
    */
   public final String getReasonCode( int index, String defaultValue )
   {
      return _ReasonCode[index] == null ? defaultValue : _ReasonCode[index];
   }
    
   /**
    * Gets the array of Reason Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reason Code values.
    */
   public final String[] getReasonCodeArray()
   {
      return _ReasonCode;
   }
    
   /**
    * Gets the Fund ID Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund ID Type or null.
    */
   public final String getrxFundIdType( int index )
   {
      return _rxFundIdType[index];
   }
    
   /**
    * Gets the Fund ID Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund ID Type or the specified default value.
    */
   public final String getrxFundIdType( int index, String defaultValue )
   {
      return _rxFundIdType[index] == null ? defaultValue : _rxFundIdType[index];
   }
    
   /**
    * Gets the array of Fund ID Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund ID Type values.
    */
   public final String[] getrxFundIdTypeArray()
   {
      return _rxFundIdType;
   }
    
   /**
    * Gets the Fund ID Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund ID Value or null.
    */
   public final String getrxFundIdValue( int index )
   {
      return _rxFundIdValue[index];
   }
    
   /**
    * Gets the Fund ID Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund ID Value or the specified default value.
    */
   public final String getrxFundIdValue( int index, String defaultValue )
   {
      return _rxFundIdValue[index] == null ? defaultValue : _rxFundIdValue[index];
   }
    
   /**
    * Gets the array of Fund ID Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund ID Value values.
    */
   public final String[] getrxFundIdValueArray()
   {
      return _rxFundIdValue;
   }
    
   /**
    * Gets the Security Recon File field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Security Recon File or null.
    */
   public final String getSecReconFile( int index )
   {
      return _SecReconFile[index];
   }
    
   /**
    * Gets the Security Recon File field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Security Recon File or the specified default value.
    */
   public final String getSecReconFile( int index, String defaultValue )
   {
      return _SecReconFile[index] == null ? defaultValue : _SecReconFile[index];
   }
    
   /**
    * Gets the array of Security Recon File fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Security Recon File values.
    */
   public final String[] getSecReconFileArray()
   {
      return _SecReconFile;
   }
    
   /**
    * Gets the Flag indicating if there is 1 processed trade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if there is 1 processed trade or null.
    */
   public final Boolean getProcessedTrade( int index )
   {
      return _ProcessedTrade[index];
   }
    
   /**
    * Gets the Flag indicating if there is 1 processed trade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if there is 1 processed trade or the specified default value.
    */
   public final boolean getProcessedTrade( int index, boolean defaultValue )
   {
      return _ProcessedTrade[index] == null ? defaultValue : _ProcessedTrade[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if there is 1 processed trade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if there is 1 processed trade values.
    */
   public final Boolean[] getProcessedTradeArray()
   {
      return _ProcessedTrade;
   }
    
   /**
    * Gets the AggrDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AggrDate or null.
    */
   public final Date getAggrDate( int index )
   {
      return _AggrDate[index];
   }
    
   /**
    * Gets the AggrDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AggrDate or the specified default value.
    */
   public final Date getAggrDate( int index, Date defaultValue )
   {
      return _AggrDate[index] == null ? defaultValue : _AggrDate[index];
   }
    
   /**
    * Gets the array of AggrDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AggrDate values.
    */
   public final Date[] getAggrDateArray()
   {
      return _AggrDate;
   }
    
   /**
    * Gets the AggrTime field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AggrTime or null.
    */
   public final String getAggrTime( int index )
   {
      return _AggrTime[index];
   }
    
   /**
    * Gets the AggrTime field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AggrTime or the specified default value.
    */
   public final String getAggrTime( int index, String defaultValue )
   {
      return _AggrTime[index] == null ? defaultValue : _AggrTime[index];
   }
    
   /**
    * Gets the array of AggrTime fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AggrTime values.
    */
   public final String[] getAggrTimeArray()
   {
      return _AggrTime;
   }
    
   /**
    * Gets the CashMsgType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CashMsgType or null.
    */
   public final String getCashMsgType( int index )
   {
      return _CashMsgType[index];
   }
    
   /**
    * Gets the CashMsgType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CashMsgType or the specified default value.
    */
   public final String getCashMsgType( int index, String defaultValue )
   {
      return _CashMsgType[index] == null ? defaultValue : _CashMsgType[index];
   }
    
   /**
    * Gets the array of CashMsgType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CashMsgType values.
    */
   public final String[] getCashMsgTypeArray()
   {
      return _CashMsgType;
   }
    
   /**
    * Gets the IntermediaryBank field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntermediaryBank or null.
    */
   public final String getIntermediaryBank( int index )
   {
      return _IntermediaryBank[index];
   }
    
   /**
    * Gets the IntermediaryBank field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntermediaryBank or the specified default value.
    */
   public final String getIntermediaryBank( int index, String defaultValue )
   {
      return _IntermediaryBank[index] == null ? defaultValue : _IntermediaryBank[index];
   }
    
   /**
    * Gets the array of IntermediaryBank fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntermediaryBank values.
    */
   public final String[] getIntermediaryBankArray()
   {
      return _IntermediaryBank;
   }
    
   /**
    * Gets the ReceivingBank field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ReceivingBank or null.
    */
   public final String getReceivingBank( int index )
   {
      return _ReceivingBank[index];
   }
    
   /**
    * Gets the ReceivingBank field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ReceivingBank or the specified default value.
    */
   public final String getReceivingBank( int index, String defaultValue )
   {
      return _ReceivingBank[index] == null ? defaultValue : _ReceivingBank[index];
   }
    
   /**
    * Gets the array of ReceivingBank fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ReceivingBank values.
    */
   public final String[] getReceivingBankArray()
   {
      return _ReceivingBank;
   }
    
   /**
    * Gets the Beneficiary field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Beneficiary or null.
    */
   public final String getBeneficiary( int index )
   {
      return _Beneficiary[index];
   }
    
   /**
    * Gets the Beneficiary field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary or the specified default value.
    */
   public final String getBeneficiary( int index, String defaultValue )
   {
      return _Beneficiary[index] == null ? defaultValue : _Beneficiary[index];
   }
    
   /**
    * Gets the array of Beneficiary fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Beneficiary values.
    */
   public final String[] getBeneficiaryArray()
   {
      return _Beneficiary;
   }
    
   /**
    * Gets the SpecialInstructions field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SpecialInstructions or null.
    */
   public final String getSpecialInstructions( int index )
   {
      return _SpecialInstructions[index];
   }
    
   /**
    * Gets the SpecialInstructions field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SpecialInstructions or the specified default value.
    */
   public final String getSpecialInstructions( int index, String defaultValue )
   {
      return _SpecialInstructions[index] == null ? defaultValue : _SpecialInstructions[index];
   }
    
   /**
    * Gets the array of SpecialInstructions fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SpecialInstructions values.
    */
   public final String[] getSpecialInstructionsArray()
   {
      return _SpecialInstructions;
   }
    
   /**
    * Gets the InternalSettlementAccount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the InternalSettlementAccount or null.
    */
   public final String getInternalSettlementAccount( int index )
   {
      return _InternalSettlementAccount[index];
   }
    
   /**
    * Gets the InternalSettlementAccount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InternalSettlementAccount or the specified default value.
    */
   public final String getInternalSettlementAccount( int index, String defaultValue )
   {
      return _InternalSettlementAccount[index] == null ? defaultValue : _InternalSettlementAccount[index];
   }
    
   /**
    * Gets the array of InternalSettlementAccount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of InternalSettlementAccount values.
    */
   public final String[] getInternalSettlementAccountArray()
   {
      return _InternalSettlementAccount;
   }
    
   /**
    * Gets the LastModStatus field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LastModStatus or null.
    */
   public final String getLastModStatus( int index )
   {
      return _LastModStatus[index];
   }
    
   /**
    * Gets the LastModStatus field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LastModStatus or the specified default value.
    */
   public final String getLastModStatus( int index, String defaultValue )
   {
      return _LastModStatus[index] == null ? defaultValue : _LastModStatus[index];
   }
    
   /**
    * Gets the array of LastModStatus fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LastModStatus values.
    */
   public final String[] getLastModStatusArray()
   {
      return _LastModStatus;
   }
    
   /**
    * Gets the CancelReqUser field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CancelReqUser or null.
    */
   public final String getCancelReqUser( int index )
   {
      return _CancelReqUser[index];
   }
    
   /**
    * Gets the CancelReqUser field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CancelReqUser or the specified default value.
    */
   public final String getCancelReqUser( int index, String defaultValue )
   {
      return _CancelReqUser[index] == null ? defaultValue : _CancelReqUser[index];
   }
    
   /**
    * Gets the array of CancelReqUser fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CancelReqUser values.
    */
   public final String[] getCancelReqUserArray()
   {
      return _CancelReqUser;
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
      
      _AggrOption = resizeArray( _AggrOption, _RepeatCount );
      _rxOmnibusId = resizeArray( _rxOmnibusId, _RepeatCount );
      _rxFundBroker = resizeArray( _rxFundBroker, _RepeatCount );
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _GroupCode = resizeArray( _GroupCode, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _AmountType = resizeArray( _AmountType, _RepeatCount );
      _TradeDate = resizeArray( _TradeDate, _RepeatCount );
      _BrkSettlDate = resizeArray( _BrkSettlDate, _RepeatCount );
      _BrkSettlAmtUnits = resizeArray( _BrkSettlAmtUnits, _RepeatCount );
      _BrkSettlPUD = resizeArray( _BrkSettlPUD, _RepeatCount );
      _AFTBenefit = resizeArray( _AFTBenefit, _RepeatCount );
      _Price = resizeArray( _Price, _RepeatCount );
      _PriceType = resizeArray( _PriceType, _RepeatCount );
      _Commission = resizeArray( _Commission, _RepeatCount );
      _ExternCharge = resizeArray( _ExternCharge, _RepeatCount );
      _RebateRate = resizeArray( _RebateRate, _RepeatCount );
      _rxOrdStatus = resizeArray( _rxOrdStatus, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _NAV = resizeArray( _NAV, _RepeatCount );
      _OfferPrice = resizeArray( _OfferPrice, _RepeatCount );
      _DeliveryTo = resizeArray( _DeliveryTo, _RepeatCount );
      _ForAccount = resizeArray( _ForAccount, _RepeatCount );
      _InFavourOf = resizeArray( _InFavourOf, _RepeatCount );
      _SettlInstrCode = resizeArray( _SettlInstrCode, _RepeatCount );
      _SettlAcctNum = resizeArray( _SettlAcctNum, _RepeatCount );
      _SettlLocCode = resizeArray( _SettlLocCode, _RepeatCount );
      _ProcessTime = resizeArray( _ProcessTime, _RepeatCount );
      _Remarks = resizeArray( _Remarks, _RepeatCount );
      _rxRoutRefNum = resizeArray( _rxRoutRefNum, _RepeatCount );
      _RoutingType = resizeArray( _RoutingType, _RepeatCount );
      _AggrOrdId = resizeArray( _AggrOrdId, _RepeatCount );
      _AggrOrdVer = resizeArray( _AggrOrdVer, _RepeatCount );
      _ClrSettlMethod = resizeArray( _ClrSettlMethod, _RepeatCount );
      _FundBrokerName = resizeArray( _FundBrokerName, _RepeatCount );
      _FundName = resizeArray( _FundName, _RepeatCount );
      _ReasonCode = resizeArray( _ReasonCode, _RepeatCount );
      _rxFundIdType = resizeArray( _rxFundIdType, _RepeatCount );
      _rxFundIdValue = resizeArray( _rxFundIdValue, _RepeatCount );
      _SecReconFile = resizeArray( _SecReconFile, _RepeatCount );
      _ProcessedTrade = resizeArray( _ProcessedTrade, _RepeatCount );
      _AggrDate = resizeArray( _AggrDate, _RepeatCount );
      _AggrTime = resizeArray( _AggrTime, _RepeatCount );
      _CashMsgType = resizeArray( _CashMsgType, _RepeatCount );
      _IntermediaryBank = resizeArray( _IntermediaryBank, _RepeatCount );
      _ReceivingBank = resizeArray( _ReceivingBank, _RepeatCount );
      _Beneficiary = resizeArray( _Beneficiary, _RepeatCount );
      _SpecialInstructions = resizeArray( _SpecialInstructions, _RepeatCount );
      _InternalSettlementAccount = resizeArray( _InternalSettlementAccount, _RepeatCount );
      _LastModStatus = resizeArray( _LastModStatus, _RepeatCount );
      _CancelReqUser = resizeArray( _CancelReqUser, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _AggrOption[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxOmnibusId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFundBroker[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GroupCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradeDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _BrkSettlDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _BrkSettlAmtUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrkSettlPUD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AFTBenefit[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Price[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PriceType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Commission[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExternCharge[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RebateRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxOrdStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _NAV[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OfferPrice[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DeliveryTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ForAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InFavourOf[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettlInstrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettlAcctNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettlLocCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxRoutRefNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RoutingType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AggrOrdId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AggrOrdVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ClrSettlMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundBrokerName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReasonCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFundIdType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFundIdValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SecReconFile[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessedTrade[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AggrDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AggrTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CashMsgType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntermediaryBank[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReceivingBank[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Beneficiary[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SpecialInstructions[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InternalSettlementAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastModStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CancelReqUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
