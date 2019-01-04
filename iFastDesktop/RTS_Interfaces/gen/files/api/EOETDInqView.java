
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * EOE Trade Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/EOETDInq.doc">EOETDInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class EOETDInqView extends IFastView implements Serializable
{

   /**
    * Trade Date member variable.
    */
   private Date _TradeDate = null;
   
   /**
    * Settlement Date member variable.
    */
   private Date _SettleDate = null;
   
   /**
    * Warning Message Code member variable.
    */
   private Integer _WarnMsgCode = null;
   

   /**
    * Constructs the EOETDInqView object.
    * 
    */
   public EOETDInqView()
   {
      super ( new EOETDInqRequest() );
   }

   /**
    * Constructs the EOETDInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public EOETDInqView( String hostEncoding )
   {
      super ( new EOETDInqRequest( hostEncoding ) );
   }

   /**
    * Gets the EOETDInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The EOETDInqRequest object.
    */
   public final EOETDInqRequest getRequest()
   {
      return (EOETDInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Trade Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Trade Date or null.
    */
   public final Date getTradeDate()
   {
      return _TradeDate;
   }
	
   /**
    * Gets the Trade Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Date or the specified default value.
    */
   public final Date getTradeDate( Date defaultValue )
   {
      return _TradeDate == null ? defaultValue : _TradeDate;
   }
                  
   /**
    * Gets the Settlement Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Settlement Date or null.
    */
   public final Date getSettleDate()
   {
      return _SettleDate;
   }
	
   /**
    * Gets the Settlement Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Date or the specified default value.
    */
   public final Date getSettleDate( Date defaultValue )
   {
      return _SettleDate == null ? defaultValue : _SettleDate;
   }
                  
   /**
    * Gets the Warning Message Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code or null.
    */
   public final Integer getWarnMsgCode()
   {
      return _WarnMsgCode;
   }
	
   /**
    * Gets the Warning Message Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code or the specified default value.
    */
   public final int getWarnMsgCode( int defaultValue )
   {
      return _WarnMsgCode == null ? defaultValue : _WarnMsgCode.intValue();
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
      _TradeDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _SettleDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _WarnMsgCode = responseBuffer.decodeInteger(responseBuffer.getNextField());
                  

   }

}
      
