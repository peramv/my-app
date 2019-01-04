
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Limitation/Setup view.
 * For additional view information see <A HREF="../../../../viewspecs/AccountLimitationSetUp.doc">AccountLimitationSetUp.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccountLimitationSetUpView extends IFastView implements Serializable
{

   /**
    * Pending Trade member variable.
    */
   private Boolean _PendingTrade = null;
   
   /**
    * Shareholder Remarks member variable.
    */
   private Boolean _Remarks = null;
   
   /**
    * Issued Certifciates member variable.
    */
   private Boolean _Certificates = null;
   
   /**
    * Stop Purchase Flag member variable.
    */
   private Boolean _StopPurchase = null;
   
   /**
    * Stop Redemption Flag member variable.
    */
   private Boolean _StopRed = null;
   
   /**
    * Stop Transfer-out member variable.
    */
   private Boolean _StopXferOut = null;
   
   /**
    * Stop Transfer-In member variable.
    */
   private Boolean _StopTXferIn = null;
   
   /**
    * Banking Instruction member variable.
    */
   private Boolean _BankingInstr = null;
   
   /**
    * Systematic Transfer member variable.
    */
   private Boolean _SystemTrsfr = null;
   
   /**
    * PAC member variable.
    */
   private Boolean _PAC = null;
   
   /**
    * SWP member variable.
    */
   private Boolean _SWP = null;
   
   /**
    * Account Allocation member variable.
    */
   private Boolean _AcctAlloc = null;
   
   /**
    * Clan Plan member variable.
    */
   private Boolean _ClanPlan = null;
   
   /**
    * Unsettled Transaction member variable.
    */
   private Boolean _UnSettledTrn = null;
   
   /**
    * Current Business Date member variable.
    */
   private Date _CurrBusDate = null;
   

   /**
    * Constructs the AccountLimitationSetUpView object.
    * 
    */
   public AccountLimitationSetUpView()
   {
      super ( new AccountLimitationSetUpRequest() );
   }

   /**
    * Constructs the AccountLimitationSetUpView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AccountLimitationSetUpView( String hostEncoding )
   {
      super ( new AccountLimitationSetUpRequest( hostEncoding ) );
   }

   /**
    * Gets the AccountLimitationSetUpRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AccountLimitationSetUpRequest object.
    */
   public final AccountLimitationSetUpRequest getRequest()
   {
      return (AccountLimitationSetUpRequest)getIFastRequest();
   }
        
   /**
    * Gets the Pending Trade field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Pending Trade or null.
    */
   public final Boolean getPendingTrade()
   {
      return _PendingTrade;
   }
	
   /**
    * Gets the Pending Trade field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pending Trade or the specified default value.
    */
   public final boolean getPendingTrade( boolean defaultValue )
   {
      return _PendingTrade == null ? defaultValue : _PendingTrade.booleanValue();
   }
                  
   /**
    * Gets the Shareholder Remarks field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Shareholder Remarks or null.
    */
   public final Boolean getRemarks()
   {
      return _Remarks;
   }
	
   /**
    * Gets the Shareholder Remarks field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Remarks or the specified default value.
    */
   public final boolean getRemarks( boolean defaultValue )
   {
      return _Remarks == null ? defaultValue : _Remarks.booleanValue();
   }
                  
   /**
    * Gets the Issued Certifciates field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Issued Certifciates or null.
    */
   public final Boolean getCertificates()
   {
      return _Certificates;
   }
	
   /**
    * Gets the Issued Certifciates field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Issued Certifciates or the specified default value.
    */
   public final boolean getCertificates( boolean defaultValue )
   {
      return _Certificates == null ? defaultValue : _Certificates.booleanValue();
   }
                  
   /**
    * Gets the Stop Purchase Flag field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Stop Purchase Flag or null.
    */
   public final Boolean getStopPurchase()
   {
      return _StopPurchase;
   }
	
   /**
    * Gets the Stop Purchase Flag field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Purchase Flag or the specified default value.
    */
   public final boolean getStopPurchase( boolean defaultValue )
   {
      return _StopPurchase == null ? defaultValue : _StopPurchase.booleanValue();
   }
                  
   /**
    * Gets the Stop Redemption Flag field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Stop Redemption Flag or null.
    */
   public final Boolean getStopRed()
   {
      return _StopRed;
   }
	
   /**
    * Gets the Stop Redemption Flag field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Redemption Flag or the specified default value.
    */
   public final boolean getStopRed( boolean defaultValue )
   {
      return _StopRed == null ? defaultValue : _StopRed.booleanValue();
   }
                  
   /**
    * Gets the Stop Transfer-out field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Stop Transfer-out or null.
    */
   public final Boolean getStopXferOut()
   {
      return _StopXferOut;
   }
	
   /**
    * Gets the Stop Transfer-out field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Transfer-out or the specified default value.
    */
   public final boolean getStopXferOut( boolean defaultValue )
   {
      return _StopXferOut == null ? defaultValue : _StopXferOut.booleanValue();
   }
                  
   /**
    * Gets the Stop Transfer-In field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Stop Transfer-In or null.
    */
   public final Boolean getStopTXferIn()
   {
      return _StopTXferIn;
   }
	
   /**
    * Gets the Stop Transfer-In field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Transfer-In or the specified default value.
    */
   public final boolean getStopTXferIn( boolean defaultValue )
   {
      return _StopTXferIn == null ? defaultValue : _StopTXferIn.booleanValue();
   }
                  
   /**
    * Gets the Banking Instruction field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Banking Instruction or null.
    */
   public final Boolean getBankingInstr()
   {
      return _BankingInstr;
   }
	
   /**
    * Gets the Banking Instruction field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Banking Instruction or the specified default value.
    */
   public final boolean getBankingInstr( boolean defaultValue )
   {
      return _BankingInstr == null ? defaultValue : _BankingInstr.booleanValue();
   }
                  
   /**
    * Gets the Systematic Transfer field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Systematic Transfer or null.
    */
   public final Boolean getSystemTrsfr()
   {
      return _SystemTrsfr;
   }
	
   /**
    * Gets the Systematic Transfer field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Systematic Transfer or the specified default value.
    */
   public final boolean getSystemTrsfr( boolean defaultValue )
   {
      return _SystemTrsfr == null ? defaultValue : _SystemTrsfr.booleanValue();
   }
                  
   /**
    * Gets the PAC field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PAC or null.
    */
   public final Boolean getPAC()
   {
      return _PAC;
   }
	
   /**
    * Gets the PAC field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAC or the specified default value.
    */
   public final boolean getPAC( boolean defaultValue )
   {
      return _PAC == null ? defaultValue : _PAC.booleanValue();
   }
                  
   /**
    * Gets the SWP field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SWP or null.
    */
   public final Boolean getSWP()
   {
      return _SWP;
   }
	
   /**
    * Gets the SWP field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SWP or the specified default value.
    */
   public final boolean getSWP( boolean defaultValue )
   {
      return _SWP == null ? defaultValue : _SWP.booleanValue();
   }
                  
   /**
    * Gets the Account Allocation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Allocation or null.
    */
   public final Boolean getAcctAlloc()
   {
      return _AcctAlloc;
   }
	
   /**
    * Gets the Account Allocation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Allocation or the specified default value.
    */
   public final boolean getAcctAlloc( boolean defaultValue )
   {
      return _AcctAlloc == null ? defaultValue : _AcctAlloc.booleanValue();
   }
                  
   /**
    * Gets the Clan Plan field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Clan Plan or null.
    */
   public final Boolean getClanPlan()
   {
      return _ClanPlan;
   }
	
   /**
    * Gets the Clan Plan field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Clan Plan or the specified default value.
    */
   public final boolean getClanPlan( boolean defaultValue )
   {
      return _ClanPlan == null ? defaultValue : _ClanPlan.booleanValue();
   }
                  
   /**
    * Gets the Unsettled Transaction field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Unsettled Transaction or null.
    */
   public final Boolean getUnSettledTrn()
   {
      return _UnSettledTrn;
   }
	
   /**
    * Gets the Unsettled Transaction field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unsettled Transaction or the specified default value.
    */
   public final boolean getUnSettledTrn( boolean defaultValue )
   {
      return _UnSettledTrn == null ? defaultValue : _UnSettledTrn.booleanValue();
   }
                  
   /**
    * Gets the Current Business Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Current Business Date or null.
    */
   public final Date getCurrBusDate()
   {
      return _CurrBusDate;
   }
	
   /**
    * Gets the Current Business Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Current Business Date or the specified default value.
    */
   public final Date getCurrBusDate( Date defaultValue )
   {
      return _CurrBusDate == null ? defaultValue : _CurrBusDate;
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
      _PendingTrade = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _Remarks = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _Certificates = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _StopPurchase = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _StopRed = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _StopXferOut = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _StopTXferIn = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _BankingInstr = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SystemTrsfr = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _PAC = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SWP = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _AcctAlloc = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ClanPlan = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _UnSettledTrn = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CurrBusDate = responseBuffer.decodeDate(responseBuffer.getNextField());
                  

   }

}
      
