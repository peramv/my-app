
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Trade Date Validation Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/TradeDateValidation.doc">TradeDateValidation.doc</A>.
 * 
 * @author RTS Generated
 */
public class TradeDateValidationView extends IFastView implements Serializable
{

   /**
    * Suggested Trade Date member variable.
    */
   private Date _SuggestTradeDate = null;
   
   /**
    * Trade Date Failed member variable.
    */
   private Boolean _TradeDateFailed = null;
   
   /**
    * Suggested Settlement Date member variable.
    */
   private Date _SuggestSettleDate = null;
   
   /**
    * Settlement Date Failed member variable.
    */
   private Boolean _SettleDateFailed = null;
   
   /**
    * Suggested Business Date member variable.
    */
   private Date _SuggestBusDate = null;
   
   /**
    * Business Date Failed member variable.
    */
   private Boolean _BusDateFailed = null;
   
   /**
    * Suggested Deal Date member variable.
    */
   private Date _SuggestDealDate = null;
   
   /**
    * Suggested Value Date member variable.
    */
   private Date _SuggestValueDate = null;
   
   /**
    * Value Date Error Code member variable.
    */
   private Integer _ValueDateErrCode = null;
   
   /**
    * Warning Message member variable.
    */
   private Integer _WarnMsgCode = null;
   
   /**
    * 60th Day of the Year member variable.
    */
   private Date _SixtiethDayOfYr = null;
   
   /**
    * Suggested Settlement Date of to side transfer/exchange member variable.
    */
   private Date _SuggestSettleInDate = null;
   
   /**
    * Rejection error number member variable.
    */
   private Integer _RejErrNum = null;
   
   /**
    * Valuation Date member variable.
    */
   private Date _rxValuationDt = null;
   

   /**
    * Constructs the TradeDateValidationView object.
    * 
    */
   public TradeDateValidationView()
   {
      super ( new TradeDateValidationRequest() );
   }

   /**
    * Constructs the TradeDateValidationView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TradeDateValidationView( String hostEncoding )
   {
      super ( new TradeDateValidationRequest( hostEncoding ) );
   }

   /**
    * Gets the TradeDateValidationRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TradeDateValidationRequest object.
    */
   public final TradeDateValidationRequest getRequest()
   {
      return (TradeDateValidationRequest)getIFastRequest();
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
    * Gets the Trade Date Failed field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Trade Date Failed or null.
    */
   public final Boolean getTradeDateFailed()
   {
      return _TradeDateFailed;
   }
	
   /**
    * Gets the Trade Date Failed field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Date Failed or the specified default value.
    */
   public final boolean getTradeDateFailed( boolean defaultValue )
   {
      return _TradeDateFailed == null ? defaultValue : _TradeDateFailed.booleanValue();
   }
                  
   /**
    * Gets the Suggested Settlement Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Suggested Settlement Date or null.
    */
   public final Date getSuggestSettleDate()
   {
      return _SuggestSettleDate;
   }
	
   /**
    * Gets the Suggested Settlement Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suggested Settlement Date or the specified default value.
    */
   public final Date getSuggestSettleDate( Date defaultValue )
   {
      return _SuggestSettleDate == null ? defaultValue : _SuggestSettleDate;
   }
                  
   /**
    * Gets the Settlement Date Failed field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Settlement Date Failed or null.
    */
   public final Boolean getSettleDateFailed()
   {
      return _SettleDateFailed;
   }
	
   /**
    * Gets the Settlement Date Failed field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Date Failed or the specified default value.
    */
   public final boolean getSettleDateFailed( boolean defaultValue )
   {
      return _SettleDateFailed == null ? defaultValue : _SettleDateFailed.booleanValue();
   }
                  
   /**
    * Gets the Suggested Business Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Suggested Business Date or null.
    */
   public final Date getSuggestBusDate()
   {
      return _SuggestBusDate;
   }
	
   /**
    * Gets the Suggested Business Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suggested Business Date or the specified default value.
    */
   public final Date getSuggestBusDate( Date defaultValue )
   {
      return _SuggestBusDate == null ? defaultValue : _SuggestBusDate;
   }
                  
   /**
    * Gets the Business Date Failed field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Business Date Failed or null.
    */
   public final Boolean getBusDateFailed()
   {
      return _BusDateFailed;
   }
	
   /**
    * Gets the Business Date Failed field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Business Date Failed or the specified default value.
    */
   public final boolean getBusDateFailed( boolean defaultValue )
   {
      return _BusDateFailed == null ? defaultValue : _BusDateFailed.booleanValue();
   }
                  
   /**
    * Gets the Suggested Deal Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Suggested Deal Date or null.
    */
   public final Date getSuggestDealDate()
   {
      return _SuggestDealDate;
   }
	
   /**
    * Gets the Suggested Deal Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suggested Deal Date or the specified default value.
    */
   public final Date getSuggestDealDate( Date defaultValue )
   {
      return _SuggestDealDate == null ? defaultValue : _SuggestDealDate;
   }
                  
   /**
    * Gets the Suggested Value Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Suggested Value Date or null.
    */
   public final Date getSuggestValueDate()
   {
      return _SuggestValueDate;
   }
	
   /**
    * Gets the Suggested Value Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suggested Value Date or the specified default value.
    */
   public final Date getSuggestValueDate( Date defaultValue )
   {
      return _SuggestValueDate == null ? defaultValue : _SuggestValueDate;
   }
                  
   /**
    * Gets the Value Date Error Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Value Date Error Code or null.
    */
   public final Integer getValueDateErrCode()
   {
      return _ValueDateErrCode;
   }
	
   /**
    * Gets the Value Date Error Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Value Date Error Code or the specified default value.
    */
   public final int getValueDateErrCode( int defaultValue )
   {
      return _ValueDateErrCode == null ? defaultValue : _ValueDateErrCode.intValue();
   }
                  
   /**
    * Gets the Warning Message field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message or null.
    */
   public final Integer getWarnMsgCode()
   {
      return _WarnMsgCode;
   }
	
   /**
    * Gets the Warning Message field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message or the specified default value.
    */
   public final int getWarnMsgCode( int defaultValue )
   {
      return _WarnMsgCode == null ? defaultValue : _WarnMsgCode.intValue();
   }
                  
   /**
    * Gets the 60th Day of the Year field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the 60th Day of the Year or null.
    */
   public final Date getSixtiethDayOfYr()
   {
      return _SixtiethDayOfYr;
   }
	
   /**
    * Gets the 60th Day of the Year field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the 60th Day of the Year or the specified default value.
    */
   public final Date getSixtiethDayOfYr( Date defaultValue )
   {
      return _SixtiethDayOfYr == null ? defaultValue : _SixtiethDayOfYr;
   }
                  
   /**
    * Gets the Suggested Settlement Date of to side transfer/exchange field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Suggested Settlement Date of to side transfer/exchange or null.
    */
   public final Date getSuggestSettleInDate()
   {
      return _SuggestSettleInDate;
   }
	
   /**
    * Gets the Suggested Settlement Date of to side transfer/exchange field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suggested Settlement Date of to side transfer/exchange or the specified default value.
    */
   public final Date getSuggestSettleInDate( Date defaultValue )
   {
      return _SuggestSettleInDate == null ? defaultValue : _SuggestSettleInDate;
   }
                  
   /**
    * Gets the Rejection error number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Rejection error number or null.
    */
   public final Integer getRejErrNum()
   {
      return _RejErrNum;
   }
	
   /**
    * Gets the Rejection error number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rejection error number or the specified default value.
    */
   public final int getRejErrNum( int defaultValue )
   {
      return _RejErrNum == null ? defaultValue : _RejErrNum.intValue();
   }
                  
   /**
    * Gets the Valuation Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Valuation Date or null.
    */
   public final Date getrxValuationDt()
   {
      return _rxValuationDt;
   }
	
   /**
    * Gets the Valuation Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Valuation Date or the specified default value.
    */
   public final Date getrxValuationDt( Date defaultValue )
   {
      return _rxValuationDt == null ? defaultValue : _rxValuationDt;
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
      _SuggestTradeDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _TradeDateFailed = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SuggestSettleDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _SettleDateFailed = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SuggestBusDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _BusDateFailed = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SuggestDealDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _SuggestValueDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ValueDateErrCode = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnMsgCode = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _SixtiethDayOfYr = responseBuffer.decodeDate(responseBuffer.getNextField());
      _SuggestSettleInDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _RejErrNum = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _rxValuationDt = responseBuffer.decodeDate(responseBuffer.getNextField());
                  

   }

}
      
