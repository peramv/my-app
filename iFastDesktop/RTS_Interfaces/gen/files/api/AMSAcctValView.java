
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * AMS Rebalancing Account Validation view.
 * For additional view information see <A HREF="../../../../viewspecs/AMSAcctVal.doc">AMSAcctVal.doc</A>.
 * 
 * @author RTS Generated
 */
public class AMSAcctValView extends IFastView implements Serializable
{

   /**
    * flag indicating if account is listed in Acct-List member variable.
    */
   private Boolean _AcctExists = null;
   
   /**
    * Accountholder name member variable.
    */
   private String _ShrName2 = null;
   
   /**
    * AMS Account Flag member variable.
    */
   private Boolean _AMSAccount = null;
   
   /**
    * flag indicating if account is deleted member variable.
    */
   private Boolean _AccountDeleted = null;
   

   /**
    * Constructs the AMSAcctValView object.
    * 
    */
   public AMSAcctValView()
   {
      super ( new AMSAcctValRequest() );
   }

   /**
    * Constructs the AMSAcctValView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AMSAcctValView( String hostEncoding )
   {
      super ( new AMSAcctValRequest( hostEncoding ) );
   }

   /**
    * Gets the AMSAcctValRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AMSAcctValRequest object.
    */
   public final AMSAcctValRequest getRequest()
   {
      return (AMSAcctValRequest)getIFastRequest();
   }
        
   /**
    * Gets the flag indicating if account is listed in Acct-List field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the flag indicating if account is listed in Acct-List or null.
    */
   public final Boolean getAcctExists()
   {
      return _AcctExists;
   }
	
   /**
    * Gets the flag indicating if account is listed in Acct-List field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the flag indicating if account is listed in Acct-List or the specified default value.
    */
   public final boolean getAcctExists( boolean defaultValue )
   {
      return _AcctExists == null ? defaultValue : _AcctExists.booleanValue();
   }
                  
   /**
    * Gets the Accountholder name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Accountholder name or null.
    */
   public final String getShrName2()
   {
      return _ShrName2;
   }
	
   /**
    * Gets the Accountholder name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Accountholder name or the specified default value.
    */
   public final String getShrName2( String defaultValue )
   {
      return _ShrName2 == null ? defaultValue : _ShrName2;
   }
                  
   /**
    * Gets the AMS Account Flag field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AMS Account Flag or null.
    */
   public final Boolean getAMSAccount()
   {
      return _AMSAccount;
   }
	
   /**
    * Gets the AMS Account Flag field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Account Flag or the specified default value.
    */
   public final boolean getAMSAccount( boolean defaultValue )
   {
      return _AMSAccount == null ? defaultValue : _AMSAccount.booleanValue();
   }
                  
   /**
    * Gets the flag indicating if account is deleted field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the flag indicating if account is deleted or null.
    */
   public final Boolean getAccountDeleted()
   {
      return _AccountDeleted;
   }
	
   /**
    * Gets the flag indicating if account is deleted field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the flag indicating if account is deleted or the specified default value.
    */
   public final boolean getAccountDeleted( boolean defaultValue )
   {
      return _AccountDeleted == null ? defaultValue : _AccountDeleted.booleanValue();
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
      _AcctExists = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ShrName2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AMSAccount = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _AccountDeleted = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
