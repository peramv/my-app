
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Assisted Contribution Amount Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AssConAmountInq.doc">AssConAmountInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AssConAmountInqView extends IFastView implements Serializable
{

   /**
    * 10 percentage of Assisted Contribution Amount member variable.
    */
   private Integer _ACAmt10Prcnt = null;
   

   /**
    * Constructs the AssConAmountInqView object.
    * 
    */
   public AssConAmountInqView()
   {
      super ( new AssConAmountInqRequest() );
   }

   /**
    * Constructs the AssConAmountInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AssConAmountInqView( String hostEncoding )
   {
      super ( new AssConAmountInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AssConAmountInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AssConAmountInqRequest object.
    */
   public final AssConAmountInqRequest getRequest()
   {
      return (AssConAmountInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the 10 percentage of Assisted Contribution Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the 10 percentage of Assisted Contribution Amount or null.
    */
   public final Integer getACAmt10Prcnt()
   {
      return _ACAmt10Prcnt;
   }
	
   /**
    * Gets the 10 percentage of Assisted Contribution Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the 10 percentage of Assisted Contribution Amount or the specified default value.
    */
   public final int getACAmt10Prcnt( int defaultValue )
   {
      return _ACAmt10Prcnt == null ? defaultValue : _ACAmt10Prcnt.intValue();
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
      _ACAmt10Prcnt = responseBuffer.decodeInteger(responseBuffer.getNextField());
                  

   }

}
      
