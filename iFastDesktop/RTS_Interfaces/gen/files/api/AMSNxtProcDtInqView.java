
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * AMS Next Process Date Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AMSNxtProcDtInq.doc">AMSNxtProcDtInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AMSNxtProcDtInqView extends IFastView implements Serializable
{

   /**
    * Next Process Date member variable.
    */
   private Date _NextProcDate = null;
   
   /**
    * Rebalance Day member variable.
    */
   private Integer _RebalanceDay = null;
   

   /**
    * Constructs the AMSNxtProcDtInqView object.
    * 
    */
   public AMSNxtProcDtInqView()
   {
      super ( new AMSNxtProcDtInqRequest() );
   }

   /**
    * Constructs the AMSNxtProcDtInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AMSNxtProcDtInqView( String hostEncoding )
   {
      super ( new AMSNxtProcDtInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AMSNxtProcDtInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AMSNxtProcDtInqRequest object.
    */
   public final AMSNxtProcDtInqRequest getRequest()
   {
      return (AMSNxtProcDtInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Next Process Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Next Process Date or null.
    */
   public final Date getNextProcDate()
   {
      return _NextProcDate;
   }
	
   /**
    * Gets the Next Process Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Next Process Date or the specified default value.
    */
   public final Date getNextProcDate( Date defaultValue )
   {
      return _NextProcDate == null ? defaultValue : _NextProcDate;
   }
                  
   /**
    * Gets the Rebalance Day field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Rebalance Day or null.
    */
   public final Integer getRebalanceDay()
   {
      return _RebalanceDay;
   }
	
   /**
    * Gets the Rebalance Day field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rebalance Day or the specified default value.
    */
   public final int getRebalanceDay( int defaultValue )
   {
      return _RebalanceDay == null ? defaultValue : _RebalanceDay.intValue();
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
      _NextProcDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _RebalanceDay = responseBuffer.decodeInteger(responseBuffer.getNextField());
                  

   }

}
      
