
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Paymnet Instuction Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/PayInstructInq.doc">PayInstructInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class PayInstructInqView extends IFastView implements Serializable
{

   /**
    * Broker Code member variable.
    */
   private String _rxBrokerCode = null;
   
   /**
    * Branch member variable.
    */
   private String _rxBranchCode = null;
   
   /**
    * Sales Rep member variable.
    */
   private String _rxSalesRepCode = null;
   
   /**
    * Payment For member variable.
    */
   private String _rxPaymentFor = null;
   
   /**
    * Effective Date member variable.
    */
   private Date _rxDeff = null;
   
   /**
    * Stop Date member variable.
    */
   private Date _rxStopDate = null;
   
   /**
    * Consolidation Type member variable.
    */
   private String _ConsolType = null;
   
   /**
    * Payment Instuction  RID member variable.
    */
   private Integer _PaymentInstructRid = null;
   

   /**
    * Constructs the PayInstructInqView object.
    * 
    */
   public PayInstructInqView()
   {
      super ( new PayInstructInqRequest() );
   }

   /**
    * Constructs the PayInstructInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PayInstructInqView( String hostEncoding )
   {
      super ( new PayInstructInqRequest( hostEncoding ) );
   }

   /**
    * Gets the PayInstructInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PayInstructInqRequest object.
    */
   public final PayInstructInqRequest getRequest()
   {
      return (PayInstructInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Broker Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Broker Code or null.
    */
   public final String getrxBrokerCode()
   {
      return _rxBrokerCode;
   }
	
   /**
    * Gets the Broker Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Code or the specified default value.
    */
   public final String getrxBrokerCode( String defaultValue )
   {
      return _rxBrokerCode == null ? defaultValue : _rxBrokerCode;
   }
                  
   /**
    * Gets the Branch field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Branch or null.
    */
   public final String getrxBranchCode()
   {
      return _rxBranchCode;
   }
	
   /**
    * Gets the Branch field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch or the specified default value.
    */
   public final String getrxBranchCode( String defaultValue )
   {
      return _rxBranchCode == null ? defaultValue : _rxBranchCode;
   }
                  
   /**
    * Gets the Sales Rep field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Sales Rep or null.
    */
   public final String getrxSalesRepCode()
   {
      return _rxSalesRepCode;
   }
	
   /**
    * Gets the Sales Rep field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep or the specified default value.
    */
   public final String getrxSalesRepCode( String defaultValue )
   {
      return _rxSalesRepCode == null ? defaultValue : _rxSalesRepCode;
   }
                  
   /**
    * Gets the Payment For field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Payment For or null.
    */
   public final String getrxPaymentFor()
   {
      return _rxPaymentFor;
   }
	
   /**
    * Gets the Payment For field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment For or the specified default value.
    */
   public final String getrxPaymentFor( String defaultValue )
   {
      return _rxPaymentFor == null ? defaultValue : _rxPaymentFor;
   }
                  
   /**
    * Gets the Effective Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Effective Date or null.
    */
   public final Date getrxDeff()
   {
      return _rxDeff;
   }
	
   /**
    * Gets the Effective Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getrxDeff( Date defaultValue )
   {
      return _rxDeff == null ? defaultValue : _rxDeff;
   }
                  
   /**
    * Gets the Stop Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Stop Date or null.
    */
   public final Date getrxStopDate()
   {
      return _rxStopDate;
   }
	
   /**
    * Gets the Stop Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getrxStopDate( Date defaultValue )
   {
      return _rxStopDate == null ? defaultValue : _rxStopDate;
   }
                  
   /**
    * Gets the Consolidation Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Consolidation Type or null.
    */
   public final String getConsolType()
   {
      return _ConsolType;
   }
	
   /**
    * Gets the Consolidation Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Consolidation Type or the specified default value.
    */
   public final String getConsolType( String defaultValue )
   {
      return _ConsolType == null ? defaultValue : _ConsolType;
   }
                  
   /**
    * Gets the Payment Instuction  RID field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Payment Instuction  RID or null.
    */
   public final Integer getPaymentInstructRid()
   {
      return _PaymentInstructRid;
   }
	
   /**
    * Gets the Payment Instuction  RID field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Instuction  RID or the specified default value.
    */
   public final int getPaymentInstructRid( int defaultValue )
   {
      return _PaymentInstructRid == null ? defaultValue : _PaymentInstructRid.intValue();
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
      _rxBrokerCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _rxBranchCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _rxSalesRepCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _rxPaymentFor = responseBuffer.decodeString(responseBuffer.getNextField());
      _rxDeff = responseBuffer.decodeDate(responseBuffer.getNextField());
      _rxStopDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ConsolType = responseBuffer.decodeString(responseBuffer.getNextField());
      _PaymentInstructRid = responseBuffer.decodeInteger(responseBuffer.getNextField());
                  

   }

}
      
