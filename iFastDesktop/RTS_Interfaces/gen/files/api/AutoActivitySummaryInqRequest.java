// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * FundCom Auto Activity Summary Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/AutoActivitySummaryInq.doc">AutoActivitySummaryInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AutoActivitySummaryInqRequest extends IFastRequest implements Serializable
{

            
   /**
    * SessionId member variable.
    */
   private String _SessionId = "";
            
   /**
    * User_Id member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * ComanyId member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Sales Rep Code member variable.
    */
   private String _SalesRepCode = "";
            
   /**
    * Fund Baycom Number member variable.
    */
   private String _Baycom = "";
            
   /**
    * Systematic Plan Indicator member variable.
    */
   private String _SystematicIndicator = "";
            

   /**
    * Constructs the AutoActivitySummaryInqRequest object.
    * 
    */
   AutoActivitySummaryInqRequest()
   {
      super ( 183 );
   }

   /**
    * Constructs the AutoActivitySummaryInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AutoActivitySummaryInqRequest( String hostEncoding )
   {
      super ( 183, hostEncoding );
   }

   /**
    * Sets the SessionId field for the request.
    * 
    * @param value  Value that the SessionId will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User_Id field for the request.
    * 
    * @param value  Value that the User_Id will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
   }
	
   /**
    * Sets the LanguageCode field for the request.
    * 
    * @param value  Value that the LanguageCode will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the ComanyId field for the request.
    * 
    * @param value  Value that the ComanyId will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Account Number field for the request.
    * 
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the Broker Code field for the request.
    * 
    * @param value  Value that the Broker Code will be set to.
    */
   public final void setBrokerCode( String value )
   {
      assertUnsent();
      _BrokerCode = value;
   }
	
   /**
    * Sets the Sales Rep Code field for the request.
    * 
    * @param value  Value that the Sales Rep Code will be set to.
    */
   public final void setSalesRepCode( String value )
   {
      assertUnsent();
      _SalesRepCode = value;
   }
	
   /**
    * Sets the Fund Baycom Number field for the request.
    * 
    * @param value  Value that the Fund Baycom Number will be set to.
    */
   public final void setBaycom( String value )
   {
      assertUnsent();
      _Baycom = value;
   }
	
   /**
    * Sets the Systematic Plan Indicator field for the request.
    * 
    * @param value  Value that the Systematic Plan Indicator will be set to.
    */
   public final void setSystematicIndicator( String value )
   {
      assertUnsent();
      _SystematicIndicator = value;
   }
	
   /**
    * Implements the abstract base method to encode
    * the host formatted request.
    * 
    * @param transaction
    *               Host formatted request object.
    */
   protected final void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
   {
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _SalesRepCode );
      requestBuffer.appendField( _Baycom );
      requestBuffer.appendField( _SystematicIndicator );
   }

}

