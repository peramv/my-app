
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Clone Maintenance view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctCloneReq.doc">AcctCloneReq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctCloneReqView extends IFastView implements Serializable
{

   /**
    * Update Status member variable.
    */
   private Boolean _UpdateStatus = null;
   
   /**
    * Shareholder Number member variable.
    */
   private Integer _ShareholderNum = null;
   
   /**
    * Account Number member variable.
    */
   private String _rxAccountNum = null;
   

   /**
    * Constructs the AcctCloneReqView object.
    * 
    */
   public AcctCloneReqView()
   {
      super ( new AcctCloneReqRequest() );
   }

   /**
    * Constructs the AcctCloneReqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctCloneReqView( String hostEncoding )
   {
      super ( new AcctCloneReqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctCloneReqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctCloneReqRequest object.
    */
   public final AcctCloneReqRequest getRequest()
   {
      return (AcctCloneReqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Update Status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Update Status or null.
    */
   public final Boolean getUpdateStatus()
   {
      return _UpdateStatus;
   }
	
   /**
    * Gets the Update Status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Update Status or the specified default value.
    */
   public final boolean getUpdateStatus( boolean defaultValue )
   {
      return _UpdateStatus == null ? defaultValue : _UpdateStatus.booleanValue();
   }
                  
   /**
    * Gets the Shareholder Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Shareholder Number or null.
    */
   public final Integer getShareholderNum()
   {
      return _ShareholderNum;
   }
	
   /**
    * Gets the Shareholder Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Number or the specified default value.
    */
   public final int getShareholderNum( int defaultValue )
   {
      return _ShareholderNum == null ? defaultValue : _ShareholderNum.intValue();
   }
                  
   /**
    * Gets the Account Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Number or null.
    */
   public final String getrxAccountNum()
   {
      return _rxAccountNum;
   }
	
   /**
    * Gets the Account Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getrxAccountNum( String defaultValue )
   {
      return _rxAccountNum == null ? defaultValue : _rxAccountNum;
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
      _UpdateStatus = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ShareholderNum = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _rxAccountNum = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
