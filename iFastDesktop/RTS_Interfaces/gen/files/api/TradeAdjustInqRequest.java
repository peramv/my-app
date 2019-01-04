// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Trade Adjust Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/TradeAdjustInq.doc">TradeAdjustInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class TradeAdjustInqRequest extends IFastRequest implements Serializable
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
    * Transaction Number member variable.
    */
   private Integer _TransNum = null;
            
   /**
    * Search Type member variable.
    */
   private String _SearchType = "";
            
   /**
    * Effective Date of Trade member variable.
    */
   private Date _TradeDate = null;
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Transaction Status member variable.
    */
   private String _TransStat = "";
            
   /**
    * Cancellation Type member variable.
    */
   private String _AdjustType = "";
            
            
   /**
    * TradeAdjust ID member variable.
    */
   private String _TradeAdjustID = "0";
            

   /**
    * Constructs the TradeAdjustInqRequest object.
    * 
    */
   TradeAdjustInqRequest()
   {
      super ( 337 );
   }

   /**
    * Constructs the TradeAdjustInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   TradeAdjustInqRequest( String hostEncoding )
   {
      super ( 337, hostEncoding );
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
    * Sets the Transaction Number field for the request.
    * 
    * @param value  Value that the Transaction Number will be set to.
    */
   public final void setTransNum( Integer value )
   {
      assertUnsent();
      _TransNum = value;
   }
	
   /**
    * Sets the Search Type field for the request.
    * 
    * @param value  Value that the Search Type will be set to.
    */
   public final void setSearchType( String value )
   {
      assertUnsent();
      _SearchType = value;
   }
	
   /**
    * Sets the Effective Date of Trade field for the request.
    * 
    * @param value  Value that the Effective Date of Trade will be set to.
    */
   public final void setTradeDate( Date value )
   {
      assertUnsent();
      _TradeDate = value;
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
    * Sets the Transaction Status field for the request.
    * 
    * @param value  Value that the Transaction Status will be set to.
    */
   public final void setTransStat( String value )
   {
      assertUnsent();
      _TransStat = value;
   }
	
   /**
    * Sets the Cancellation Type field for the request.
    * 
    * @param value  Value that the Cancellation Type will be set to.
    */
   public final void setAdjustType( String value )
   {
      assertUnsent();
      _AdjustType = value;
   }
	
   /**
    * Sets the TradeAdjust ID field for the request.
    * 
    * @param value  Value that the TradeAdjust ID will be set to.
    */
   public final void setTradeAdjustID( String value )
   {
      assertUnsent();
      _TradeAdjustID = value;
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
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _TransNum );
      requestBuffer.appendField( _SearchType );
      requestBuffer.appendField( _TradeDate );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _TransStat );
      requestBuffer.appendField( _AdjustType );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _TradeAdjustID );
   }

}

