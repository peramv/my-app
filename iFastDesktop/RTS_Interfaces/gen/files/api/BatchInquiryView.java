
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Batch Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/BatchInquiry.doc">BatchInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class BatchInquiryView extends IFastView implements Serializable
{

   /**
    * Response Batch Name member variable.
    */
   private String _rxBatchName = null;
   
   /**
    * Flag confirming input and output batch is the same member variable.
    */
   private Boolean _SameBatchName = null;
   
   /**
    * Batch order type member variable.
    */
   private String _BatchOrdType = null;
   
   /**
    * Batch trace member variable.
    */
   private Integer _BatchTrace = null;
   
   /**
    * Effective Date for this Batch member variable.
    */
   private Date _EffectiveDate = null;
   
   /**
    * Check Closed Batch member variable.
    */
   private Boolean _CheckClosedBatch = null;
   
   /**
    * Flag indicating if batch id passed belongs to the same user member variable.
    */
   private Boolean _SameUserBatch = null;
   
   /**
    * Server Time member variable.
    */
   private String _Servertime = null;
   

   /**
    * Constructs the BatchInquiryView object.
    * 
    */
   public BatchInquiryView()
   {
      super ( new BatchInquiryRequest() );
   }

   /**
    * Constructs the BatchInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public BatchInquiryView( String hostEncoding )
   {
      super ( new BatchInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the BatchInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The BatchInquiryRequest object.
    */
   public final BatchInquiryRequest getRequest()
   {
      return (BatchInquiryRequest)getIFastRequest();
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
    * Gets the Batch order type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Batch order type or null.
    */
   public final String getBatchOrdType()
   {
      return _BatchOrdType;
   }
	
   /**
    * Gets the Batch order type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch order type or the specified default value.
    */
   public final String getBatchOrdType( String defaultValue )
   {
      return _BatchOrdType == null ? defaultValue : _BatchOrdType;
   }
                  
   /**
    * Gets the Batch trace field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Batch trace or null.
    */
   public final Integer getBatchTrace()
   {
      return _BatchTrace;
   }
	
   /**
    * Gets the Batch trace field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch trace or the specified default value.
    */
   public final int getBatchTrace( int defaultValue )
   {
      return _BatchTrace == null ? defaultValue : _BatchTrace.intValue();
   }
                  
   /**
    * Gets the Effective Date for this Batch field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Effective Date for this Batch or null.
    */
   public final Date getEffectiveDate()
   {
      return _EffectiveDate;
   }
	
   /**
    * Gets the Effective Date for this Batch field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date for this Batch or the specified default value.
    */
   public final Date getEffectiveDate( Date defaultValue )
   {
      return _EffectiveDate == null ? defaultValue : _EffectiveDate;
   }
                  
   /**
    * Gets the Check Closed Batch field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Check Closed Batch or null.
    */
   public final Boolean getCheckClosedBatch()
   {
      return _CheckClosedBatch;
   }
	
   /**
    * Gets the Check Closed Batch field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Check Closed Batch or the specified default value.
    */
   public final boolean getCheckClosedBatch( boolean defaultValue )
   {
      return _CheckClosedBatch == null ? defaultValue : _CheckClosedBatch.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if batch id passed belongs to the same user field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if batch id passed belongs to the same user or null.
    */
   public final Boolean getSameUserBatch()
   {
      return _SameUserBatch;
   }
	
   /**
    * Gets the Flag indicating if batch id passed belongs to the same user field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if batch id passed belongs to the same user or the specified default value.
    */
   public final boolean getSameUserBatch( boolean defaultValue )
   {
      return _SameUserBatch == null ? defaultValue : _SameUserBatch.booleanValue();
   }
                  
   /**
    * Gets the Server Time field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Server Time or null.
    */
   public final String getServertime()
   {
      return _Servertime;
   }
	
   /**
    * Gets the Server Time field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Server Time or the specified default value.
    */
   public final String getServertime( String defaultValue )
   {
      return _Servertime == null ? defaultValue : _Servertime;
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
      _rxBatchName = responseBuffer.decodeString(responseBuffer.getNextField());
      _SameBatchName = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _BatchOrdType = responseBuffer.decodeString(responseBuffer.getNextField());
      _BatchTrace = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _EffectiveDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _CheckClosedBatch = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SameUserBatch = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _Servertime = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
