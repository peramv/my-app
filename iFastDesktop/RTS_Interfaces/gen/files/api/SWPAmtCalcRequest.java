// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * SWP Amount Calculation for GWA/LWA Option request.
 * For additional view information see <A HREF="../../../../viewspecs/SWPAmtCalc.doc">SWPAmtCalc.doc</A>.
 * 
 * @author RTS Generated
 */
public class SWPAmtCalcRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
   /**
    * User ID member variable.
    */
   private String _User_ID = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyID = "";
            
            
            
   /**
    * Account Num member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Amount Type member variable.
    */
   private String _AmountType = "";
            
   /**
    * Bank Detl Effective Date member variable.
    */
   private Date _BankDetlDeff = null;
            
   /**
    * Bank Detl Stop Date member variable.
    */
   private Date _BankDetlStopDate = null;
            
   /**
    * End of the Month flag member variable.
    */
   private Boolean _EndOfMonth = new Boolean(false);
            
   /**
    * January member variable.
    */
   private Boolean _January = new Boolean(false);
            
   /**
    * February member variable.
    */
   private Boolean _February = new Boolean(false);
            
   /**
    * March member variable.
    */
   private Boolean _March = new Boolean(false);
            
   /**
    * April member variable.
    */
   private Boolean _April = new Boolean(false);
            
   /**
    * May member variable.
    */
   private Boolean _May = new Boolean(false);
            
   /**
    * June member variable.
    */
   private Boolean _June = new Boolean(false);
            
   /**
    * July member variable.
    */
   private Boolean _July = new Boolean(false);
            
   /**
    * August member variable.
    */
   private Boolean _August = new Boolean(false);
            
   /**
    * September member variable.
    */
   private Boolean _September = new Boolean(false);
            
   /**
    * October member variable.
    */
   private Boolean _October = new Boolean(false);
            
   /**
    * November member variable.
    */
   private Boolean _November = new Boolean(false);
            
   /**
    * December member variable.
    */
   private Boolean _December = new Boolean(false);
            

   /**
    * Constructs the SWPAmtCalcRequest object.
    * 
    */
   SWPAmtCalcRequest()
   {
      super ( 437 );
   }

   /**
    * Constructs the SWPAmtCalcRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SWPAmtCalcRequest( String hostEncoding )
   {
      super ( 437, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
    */
   public final void setUser_ID( String value )
   {
      assertUnsent();
      _User_ID = value;
   }
	
   /**
    * Sets the Language Code field for the request.
    * 
    * @param value  Value that the Language Code will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the Company ID field for the request.
    * 
    * @param value  Value that the Company ID will be set to.
    */
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
   }
	
   /**
    * Sets the Account Num field for the request.
    * 
    * @param value  Value that the Account Num will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the Amount Type field for the request.
    * 
    * @param value  Value that the Amount Type will be set to.
    */
   public final void setAmountType( String value )
   {
      assertUnsent();
      _AmountType = value;
   }
	
   /**
    * Sets the Bank Detl Effective Date field for the request.
    * 
    * @param value  Value that the Bank Detl Effective Date will be set to.
    */
   public final void setBankDetlDeff( Date value )
   {
      assertUnsent();
      _BankDetlDeff = value;
   }
	
   /**
    * Sets the Bank Detl Stop Date field for the request.
    * 
    * @param value  Value that the Bank Detl Stop Date will be set to.
    */
   public final void setBankDetlStopDate( Date value )
   {
      assertUnsent();
      _BankDetlStopDate = value;
   }
	
   /**
    * Sets the End of the Month flag field for the request.
    * 
    * @param value  Value that the End of the Month flag will be set to.
    */
   public final void setEndOfMonth( Boolean value )
   {
      assertUnsent();
      _EndOfMonth = value;
   }
	
   /**
    * Sets the January field for the request.
    * 
    * @param value  Value that the January will be set to.
    */
   public final void setJanuary( Boolean value )
   {
      assertUnsent();
      _January = value;
   }
	
   /**
    * Sets the February field for the request.
    * 
    * @param value  Value that the February will be set to.
    */
   public final void setFebruary( Boolean value )
   {
      assertUnsent();
      _February = value;
   }
	
   /**
    * Sets the March field for the request.
    * 
    * @param value  Value that the March will be set to.
    */
   public final void setMarch( Boolean value )
   {
      assertUnsent();
      _March = value;
   }
	
   /**
    * Sets the April field for the request.
    * 
    * @param value  Value that the April will be set to.
    */
   public final void setApril( Boolean value )
   {
      assertUnsent();
      _April = value;
   }
	
   /**
    * Sets the May field for the request.
    * 
    * @param value  Value that the May will be set to.
    */
   public final void setMay( Boolean value )
   {
      assertUnsent();
      _May = value;
   }
	
   /**
    * Sets the June field for the request.
    * 
    * @param value  Value that the June will be set to.
    */
   public final void setJune( Boolean value )
   {
      assertUnsent();
      _June = value;
   }
	
   /**
    * Sets the July field for the request.
    * 
    * @param value  Value that the July will be set to.
    */
   public final void setJuly( Boolean value )
   {
      assertUnsent();
      _July = value;
   }
	
   /**
    * Sets the August field for the request.
    * 
    * @param value  Value that the August will be set to.
    */
   public final void setAugust( Boolean value )
   {
      assertUnsent();
      _August = value;
   }
	
   /**
    * Sets the September field for the request.
    * 
    * @param value  Value that the September will be set to.
    */
   public final void setSeptember( Boolean value )
   {
      assertUnsent();
      _September = value;
   }
	
   /**
    * Sets the October field for the request.
    * 
    * @param value  Value that the October will be set to.
    */
   public final void setOctober( Boolean value )
   {
      assertUnsent();
      _October = value;
   }
	
   /**
    * Sets the November field for the request.
    * 
    * @param value  Value that the November will be set to.
    */
   public final void setNovember( Boolean value )
   {
      assertUnsent();
      _November = value;
   }
	
   /**
    * Sets the December field for the request.
    * 
    * @param value  Value that the December will be set to.
    */
   public final void setDecember( Boolean value )
   {
      assertUnsent();
      _December = value;
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
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _AmountType );
      requestBuffer.appendField( _BankDetlDeff );
      requestBuffer.appendField( _BankDetlStopDate );
      requestBuffer.appendField( _EndOfMonth );
      requestBuffer.appendField( _January );
      requestBuffer.appendField( _February );
      requestBuffer.appendField( _March );
      requestBuffer.appendField( _April );
      requestBuffer.appendField( _May );
      requestBuffer.appendField( _June );
      requestBuffer.appendField( _July );
      requestBuffer.appendField( _August );
      requestBuffer.appendField( _September );
      requestBuffer.appendField( _October );
      requestBuffer.appendField( _November );
      requestBuffer.appendField( _December );
   }

}

