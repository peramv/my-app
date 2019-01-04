
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Transaction Number  Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/TransactionNumberInquiry.doc">TransactionNumberInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class TransactionNumberInquiryView extends IFastView implements Serializable
{

   /**
    * Transaction Number member variable.
    */
   private Integer _TransNum = null;
   
   /**
    * Deal Time member variable.
    */
   private String _DealTime = null;
   
   /**
    * Current Business Date member variable.
    */
   private Date _CurrBusDate = null;
   
   /**
    * Today's Date (Default Trade Date) member variable.
    */
   private Date _DealDate = null;
   
   /**
    * Response Batch Name member variable.
    */
   private String _rxBatchName = null;
   
   /**
    * Flag confirming input and output batch is the same member variable.
    */
   private Boolean _SameBatchName = null;
   
   /**
    * Batch Order Type member variable.
    */
   private Boolean _BatchOrdType = null;
   
   /**
    * Transaction Trace Number within Current Batch member variable.
    */
   private Integer _BatchTrace = null;
   
   /**
    * Batch Effective Date member variable.
    */
   private Date _EffectiveDate = null;
   
   /**
    * Payment Type member variable.
    */
   private String _rxPayType = null;
   
   /**
    * Transaction Type member variable.
    */
   private String _rxTransType = null;
   
   /**
    * Suggested Trade Date member variable.
    */
   private Date _SuggestTradeDate = null;
   
   /**
    * Suggested Settle Date member variable.
    */
   private Date _SuggestSettleDate = null;
   
   /**
    * Suggested Settle In Date member variable.
    */
   private Date _SuggestSettleInDate = null;
   

   /**
    * Constructs the TransactionNumberInquiryView object.
    * 
    */
   public TransactionNumberInquiryView()
   {
      super ( new TransactionNumberInquiryRequest() );
   }

   /**
    * Constructs the TransactionNumberInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TransactionNumberInquiryView( String hostEncoding )
   {
      super ( new TransactionNumberInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the TransactionNumberInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TransactionNumberInquiryRequest object.
    */
   public final TransactionNumberInquiryRequest getRequest()
   {
      return (TransactionNumberInquiryRequest)getIFastRequest();
   }
        
   /**
    * Gets the Transaction Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Transaction Number or null.
    */
   public final Integer getTransNum()
   {
      return _TransNum;
   }
	
   /**
    * Gets the Transaction Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Number or the specified default value.
    */
   public final int getTransNum( int defaultValue )
   {
      return _TransNum == null ? defaultValue : _TransNum.intValue();
   }
                  
   /**
    * Gets the Deal Time field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Deal Time or null.
    */
   public final String getDealTime()
   {
      return _DealTime;
   }
	
   /**
    * Gets the Deal Time field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deal Time or the specified default value.
    */
   public final String getDealTime( String defaultValue )
   {
      return _DealTime == null ? defaultValue : _DealTime;
   }
                  
   /**
    * Gets the Current Business Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Current Business Date or null.
    */
   public final Date getCurrBusDate()
   {
      return _CurrBusDate;
   }
	
   /**
    * Gets the Current Business Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Current Business Date or the specified default value.
    */
   public final Date getCurrBusDate( Date defaultValue )
   {
      return _CurrBusDate == null ? defaultValue : _CurrBusDate;
   }
                  
   /**
    * Gets the Today's Date (Default Trade Date) field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Today's Date (Default Trade Date) or null.
    */
   public final Date getDealDate()
   {
      return _DealDate;
   }
	
   /**
    * Gets the Today's Date (Default Trade Date) field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Today's Date (Default Trade Date) or the specified default value.
    */
   public final Date getDealDate( Date defaultValue )
   {
      return _DealDate == null ? defaultValue : _DealDate;
   }
                  
   /**
    * Gets the Response Batch Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Response Batch Name or null.
    */
   public final String getrxBatchName()
   {
      return _rxBatchName;
   }
	
   /**
    * Gets the Response Batch Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Response Batch Name or the specified default value.
    */
   public final String getrxBatchName( String defaultValue )
   {
      return _rxBatchName == null ? defaultValue : _rxBatchName;
   }
                  
   /**
    * Gets the Flag confirming input and output batch is the same field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag confirming input and output batch is the same or null.
    */
   public final Boolean getSameBatchName()
   {
      return _SameBatchName;
   }
	
   /**
    * Gets the Flag confirming input and output batch is the same field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag confirming input and output batch is the same or the specified default value.
    */
   public final boolean getSameBatchName( boolean defaultValue )
   {
      return _SameBatchName == null ? defaultValue : _SameBatchName.booleanValue();
   }
                  
   /**
    * Gets the Batch Order Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Batch Order Type or null.
    */
   public final Boolean getBatchOrdType()
   {
      return _BatchOrdType;
   }
	
   /**
    * Gets the Batch Order Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Order Type or the specified default value.
    */
   public final boolean getBatchOrdType( boolean defaultValue )
   {
      return _BatchOrdType == null ? defaultValue : _BatchOrdType.booleanValue();
   }
                  
   /**
    * Gets the Transaction Trace Number within Current Batch field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Transaction Trace Number within Current Batch or null.
    */
   public final Integer getBatchTrace()
   {
      return _BatchTrace;
   }
	
   /**
    * Gets the Transaction Trace Number within Current Batch field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Trace Number within Current Batch or the specified default value.
    */
   public final int getBatchTrace( int defaultValue )
   {
      return _BatchTrace == null ? defaultValue : _BatchTrace.intValue();
   }
                  
   /**
    * Gets the Batch Effective Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Batch Effective Date or null.
    */
   public final Date getEffectiveDate()
   {
      return _EffectiveDate;
   }
	
   /**
    * Gets the Batch Effective Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( Date defaultValue )
   {
      return _EffectiveDate == null ? defaultValue : _EffectiveDate;
   }
                  
   /**
    * Gets the Payment Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Payment Type or null.
    */
   public final String getrxPayType()
   {
      return _rxPayType;
   }
	
   /**
    * Gets the Payment Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Type or the specified default value.
    */
   public final String getrxPayType( String defaultValue )
   {
      return _rxPayType == null ? defaultValue : _rxPayType;
   }
                  
   /**
    * Gets the Transaction Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Transaction Type or null.
    */
   public final String getrxTransType()
   {
      return _rxTransType;
   }
	
   /**
    * Gets the Transaction Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Type or the specified default value.
    */
   public final String getrxTransType( String defaultValue )
   {
      return _rxTransType == null ? defaultValue : _rxTransType;
   }
                  
   /**
    * Gets the Suggested Trade Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Suggested Trade Date or null.
    */
   public final Date getSuggestTradeDate()
   {
      return _SuggestTradeDate;
   }
	
   /**
    * Gets the Suggested Trade Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suggested Trade Date or the specified default value.
    */
   public final Date getSuggestTradeDate( Date defaultValue )
   {
      return _SuggestTradeDate == null ? defaultValue : _SuggestTradeDate;
   }
                  
   /**
    * Gets the Suggested Settle Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Suggested Settle Date or null.
    */
   public final Date getSuggestSettleDate()
   {
      return _SuggestSettleDate;
   }
	
   /**
    * Gets the Suggested Settle Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suggested Settle Date or the specified default value.
    */
   public final Date getSuggestSettleDate( Date defaultValue )
   {
      return _SuggestSettleDate == null ? defaultValue : _SuggestSettleDate;
   }
                  
   /**
    * Gets the Suggested Settle In Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Suggested Settle In Date or null.
    */
   public final Date getSuggestSettleInDate()
   {
      return _SuggestSettleInDate;
   }
	
   /**
    * Gets the Suggested Settle In Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suggested Settle In Date or the specified default value.
    */
   public final Date getSuggestSettleInDate( Date defaultValue )
   {
      return _SuggestSettleInDate == null ? defaultValue : _SuggestSettleInDate;
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
      _TransNum = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _DealTime = responseBuffer.decodeString(responseBuffer.getNextField());
      _CurrBusDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _DealDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _rxBatchName = responseBuffer.decodeString(responseBuffer.getNextField());
      _SameBatchName = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _BatchOrdType = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _BatchTrace = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _EffectiveDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _rxPayType = responseBuffer.decodeString(responseBuffer.getNextField());
      _rxTransType = responseBuffer.decodeString(responseBuffer.getNextField());
      _SuggestTradeDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _SuggestSettleDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _SuggestSettleInDate = responseBuffer.decodeDate(responseBuffer.getNextField());
                  

   }

}
      
