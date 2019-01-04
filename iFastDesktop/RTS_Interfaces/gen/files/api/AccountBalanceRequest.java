// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account/fund balances request.
 * For additional view information see <A HREF="../../../../viewspecs/AccountBalance.doc">AccountBalance.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccountBalanceRequest extends IFastRequest implements Serializable
{

   /**
    * Account member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * As of Date member variable.
    */
   private Date _AsofDate = null;
            
            
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
    * Calculate ACB member variable.
    */
   private Boolean _CalculateACB = new Boolean(false);
            
   /**
    * Active Only member variable.
    */
   private Boolean _ActiveOnly = new Boolean(false);
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Reporting Currency member variable.
    */
   private String _ReportingCurrency = "";
            
   /**
    * Convert Amount to preferred currency (Yes/No) member variable.
    */
   private Boolean _ConvertAmount = new Boolean(false);
            
   /**
    * Account Balance Mode member variable.
    */
   private String _AccBalMode = "";
            

   /**
    * Constructs the AccountBalanceRequest object.
    * 
    */
   AccountBalanceRequest()
   {
      super ( 20 );
   }

   /**
    * Constructs the AccountBalanceRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AccountBalanceRequest( String hostEncoding )
   {
      super ( 20, hostEncoding );
   }

   /**
    * Sets the Account field for the request.
    * 
    * @param value  Value that the Account will be set to.
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
   public final void setAsofDate( Date value )
   {
      assertUnsent();
      _AsofDate = value;
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
    * Sets the Calculate ACB field for the request.
    * 
    * @param value  Value that the Calculate ACB will be set to.
    */
   public final void setCalculateACB( Boolean value )
   {
      assertUnsent();
      _CalculateACB = value;
   }
	
   /**
    * Sets the Active Only field for the request.
    * 
    * @param value  Value that the Active Only will be set to.
    */
   public final void setActiveOnly( Boolean value )
   {
      assertUnsent();
      _ActiveOnly = value;
   }
	
   /**
    * Sets the Fund Code field for the request.
    * 
    * @param value  Value that the Fund Code will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class Code field for the request.
    * 
    * @param value  Value that the Class Code will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
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
    * Sets the Convert Amount to preferred currency (Yes/No) field for the request.
    * 
    * @param value  Value that the Convert Amount to preferred currency (Yes/No) will be set to.
    */
   public final void setConvertAmount( Boolean value )
   {
      assertUnsent();
      _ConvertAmount = value;
   }
	
   /**
    * Sets the Account Balance Mode field for the request.
    * 
    * @param value  Value that the Account Balance Mode will be set to.
    */
   public final void setAccBalMode( String value )
   {
      assertUnsent();
      _AccBalMode = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _AsofDate );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _CalculateACB );
      requestBuffer.appendField( _ActiveOnly );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _ReportingCurrency );
      requestBuffer.appendField( _ConvertAmount );
      requestBuffer.appendField( _AccBalMode );
   }

}

