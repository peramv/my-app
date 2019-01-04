// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Details and Holdings request.
 * For additional view information see <A HREF="../../../../viewspecs/AccountDetailsAndHoldings.doc">AccountDetailsAndHoldings.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccountDetailsAndHoldingsRequest extends IFastRequest implements Serializable
{

            
   /**
    * SessionId member variable.
    */
   private String _SessionId = "";
            
   /**
    * UserId member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * CompanyId member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
            
   /**
    * As of Date member variable.
    */
   private Date _AsOfDate = null;
            
   /**
    * Reporting Currency member variable.
    */
   private String _ReportingCurrency = "";
            

   /**
    * Constructs the AccountDetailsAndHoldingsRequest object.
    * 
    */
   AccountDetailsAndHoldingsRequest()
   {
      super ( 166 );
   }

   /**
    * Constructs the AccountDetailsAndHoldingsRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AccountDetailsAndHoldingsRequest( String hostEncoding )
   {
      super ( 166, hostEncoding );
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
    * Sets the UserId field for the request.
    * 
    * @param value  Value that the UserId will be set to.
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
    * Sets the CompanyId field for the request.
    * 
    * @param value  Value that the CompanyId will be set to.
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
    * Sets the As of Date field for the request.
    * 
    * @param value  Value that the As of Date will be set to.
    */
   public final void setAsOfDate( Date value )
   {
      assertUnsent();
      _AsOfDate = value;
   }
	
   /**
    * Sets the Reporting Currency field for the request.
    * 
    * @param value  Value that the Reporting Currency will be set to.
    */
   public final void setReportingCurrency( String value )
   {
      assertUnsent();
      _ReportingCurrency = value;
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
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _AsOfDate );
      requestBuffer.appendField( _ReportingCurrency );
   }

}

