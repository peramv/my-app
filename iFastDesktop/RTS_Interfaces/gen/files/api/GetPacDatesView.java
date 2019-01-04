
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * RESP Diploma Get PAC Dates view.
 * For additional view information see <A HREF="../../../../viewspecs/GetPacDates.doc">GetPacDates.doc</A>.
 * 
 * @author RTS Generated
 */
public class GetPacDatesView extends IFastView implements Serializable
{

   /**
    * New PAC Effective Date member variable.
    */
   private Date _NewPACDeff = null;
   
   /**
    * Next PAC Process Date member variable.
    */
   private Date _NextProcDate = null;
   

   /**
    * Constructs the GetPacDatesView object.
    * 
    */
   public GetPacDatesView()
   {
      super ( new GetPacDatesRequest() );
   }

   /**
    * Constructs the GetPacDatesView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public GetPacDatesView( String hostEncoding )
   {
      super ( new GetPacDatesRequest( hostEncoding ) );
   }

   /**
    * Gets the GetPacDatesRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The GetPacDatesRequest object.
    */
   public final GetPacDatesRequest getRequest()
   {
      return (GetPacDatesRequest)getIFastRequest();
   }
        
   /**
    * Gets the New PAC Effective Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the New PAC Effective Date or null.
    */
   public final Date getNewPACDeff()
   {
      return _NewPACDeff;
   }
	
   /**
    * Gets the New PAC Effective Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the New PAC Effective Date or the specified default value.
    */
   public final Date getNewPACDeff( Date defaultValue )
   {
      return _NewPACDeff == null ? defaultValue : _NewPACDeff;
   }
                  
   /**
    * Gets the Next PAC Process Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Next PAC Process Date or null.
    */
   public final Date getNextProcDate()
   {
      return _NextProcDate;
   }
	
   /**
    * Gets the Next PAC Process Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Next PAC Process Date or the specified default value.
    */
   public final Date getNextProcDate( Date defaultValue )
   {
      return _NextProcDate == null ? defaultValue : _NextProcDate;
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
      _NewPACDeff = responseBuffer.decodeDate(responseBuffer.getNextField());
      _NextProcDate = responseBuffer.decodeDate(responseBuffer.getNextField());
                  

   }

}
      
