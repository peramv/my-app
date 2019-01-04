// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * GIA Investment List Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/GIAInvestmentListInquiry.doc">GIAInvestmentListInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class GIAInvestmentListInquiryRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionId = "";
            
   /**
    * User Id member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
            
   /**
    * InputAcctNum member variable.
    */
   private String _InputAcctNum = "0";
            
   /**
    * SearchBy member variable.
    */
   private String _SearchBy = "";
            
   /**
    * SearchFund member variable.
    */
   private String _SearchFund = "";
            
   /**
    * SearchClass member variable.
    */
   private String _SearchClass = "";
            
   /**
    * SearchInvestmentNo member variable.
    */
   private String _SearchInvestmentNo = "";
            
   /**
    * SearchInvestStatus member variable.
    */
   private String _SearchInvestStatus = "";
            
   /**
    * SearchTransId member variable.
    */
   private String _SearchTransId = "0";
            
   /**
    * rxTradeDate member variable.
    */
   private Date _rxTradeDate = null;
            
   /**
    * rxGrossNet member variable.
    */
   private Boolean _rxGrossNet = new Boolean(false);
            
   /**
    * rxRedemOrder member variable.
    */
   private String _rxRedemOrder = "";
            
   /**
    * AmtType of cherry pick record member variable.
    */
   private String _rxAmtType = "";
            
   /**
    * Amount of cherry pick record member variable.
    */
   private String _rxAmount = "0";
            
   /**
    * rxSupressMVA member variable.
    */
   private Boolean _rxSupressMVA = new Boolean(false);
            
   /**
    * rxSupressAdmin member variable.
    */
   private Boolean _rxSupressAdmin = new Boolean(false);
            
   /**
    * rxIntInvestId member variable.
    */
   private String _rxIntInvestId = "0";
            
   /**
    * rxInvSummId member variable.
    */
   private Integer _rxInvSummId = null;
            
   /**
    * Trade Amount member variable.
    */
   private String _rxTradeAmount = "0";
            

   /**
    * Constructs the GIAInvestmentListInquiryRequest object.
    * 
    */
   GIAInvestmentListInquiryRequest()
   {
      super ( 421 );
   }

   /**
    * Constructs the GIAInvestmentListInquiryRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   GIAInvestmentListInquiryRequest( String hostEncoding )
   {
      super ( 421, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User Id field for the request.
    * 
    * @param value  Value that the User Id will be set to.
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
    * Sets the Company Id field for the request.
    * 
    * @param value  Value that the Company Id will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the InputAcctNum field for the request.
    * 
    * @param value  Value that the InputAcctNum will be set to.
    */
   public final void setInputAcctNum( String value )
   {
      assertUnsent();
      _InputAcctNum = value;
   }
	
   /**
    * Sets the SearchBy field for the request.
    * 
    * @param value  Value that the SearchBy will be set to.
    */
   public final void setSearchBy( String value )
   {
      assertUnsent();
      _SearchBy = value;
   }
	
   /**
    * Sets the SearchFund field for the request.
    * 
    * @param value  Value that the SearchFund will be set to.
    */
   public final void setSearchFund( String value )
   {
      assertUnsent();
      _SearchFund = value;
   }
	
   /**
    * Sets the SearchClass field for the request.
    * 
    * @param value  Value that the SearchClass will be set to.
    */
   public final void setSearchClass( String value )
   {
      assertUnsent();
      _SearchClass = value;
   }
	
   /**
    * Sets the SearchInvestmentNo field for the request.
    * 
    * @param value  Value that the SearchInvestmentNo will be set to.
    */
   public final void setSearchInvestmentNo( String value )
   {
      assertUnsent();
      _SearchInvestmentNo = value;
   }
	
   /**
    * Sets the SearchInvestStatus field for the request.
    * 
    * @param value  Value that the SearchInvestStatus will be set to.
    */
   public final void setSearchInvestStatus( String value )
   {
      assertUnsent();
      _SearchInvestStatus = value;
   }
	
   /**
    * Sets the SearchTransId field for the request.
    * 
    * @param value  Value that the SearchTransId will be set to.
    */
   public final void setSearchTransId( String value )
   {
      assertUnsent();
      _SearchTransId = value;
   }
	
   /**
    * Sets the rxTradeDate field for the request.
    * 
    * @param value  Value that the rxTradeDate will be set to.
    */
   public final void setrxTradeDate( Date value )
   {
      assertUnsent();
      _rxTradeDate = value;
   }
	
   /**
    * Sets the rxGrossNet field for the request.
    * 
    * @param value  Value that the rxGrossNet will be set to.
    */
   public final void setrxGrossNet( Boolean value )
   {
      assertUnsent();
      _rxGrossNet = value;
   }
	
   /**
    * Sets the rxRedemOrder field for the request.
    * 
    * @param value  Value that the rxRedemOrder will be set to.
    */
   public final void setrxRedemOrder( String value )
   {
      assertUnsent();
      _rxRedemOrder = value;
   }
	
   /**
    * Sets the AmtType of cherry pick record field for the request.
    * 
    * @param value  Value that the AmtType of cherry pick record will be set to.
    */
   public final void setrxAmtType( String value )
   {
      assertUnsent();
      _rxAmtType = value;
   }
	
   /**
    * Sets the Amount of cherry pick record field for the request.
    * 
    * @param value  Value that the Amount of cherry pick record will be set to.
    */
   public final void setrxAmount( String value )
   {
      assertUnsent();
      _rxAmount = value;
   }
	
   /**
    * Sets the rxSupressMVA field for the request.
    * 
    * @param value  Value that the rxSupressMVA will be set to.
    */
   public final void setrxSupressMVA( Boolean value )
   {
      assertUnsent();
      _rxSupressMVA = value;
   }
	
   /**
    * Sets the rxSupressAdmin field for the request.
    * 
    * @param value  Value that the rxSupressAdmin will be set to.
    */
   public final void setrxSupressAdmin( Boolean value )
   {
      assertUnsent();
      _rxSupressAdmin = value;
   }
	
   /**
    * Sets the rxIntInvestId field for the request.
    * 
    * @param value  Value that the rxIntInvestId will be set to.
    */
   public final void setrxIntInvestId( String value )
   {
      assertUnsent();
      _rxIntInvestId = value;
   }
	
   /**
    * Sets the rxInvSummId field for the request.
    * 
    * @param value  Value that the rxInvSummId will be set to.
    */
   public final void setrxInvSummId( Integer value )
   {
      assertUnsent();
      _rxInvSummId = value;
   }
	
   /**
    * Sets the Trade Amount field for the request.
    * 
    * @param value  Value that the Trade Amount will be set to.
    */
   public final void setrxTradeAmount( String value )
   {
      assertUnsent();
      _rxTradeAmount = value;
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
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _InputAcctNum );
      requestBuffer.appendField( _SearchBy );
      requestBuffer.appendField( _SearchFund );
      requestBuffer.appendField( _SearchClass );
      requestBuffer.appendField( _SearchInvestmentNo );
      requestBuffer.appendField( _SearchInvestStatus );
      requestBuffer.appendField( _SearchTransId );
      requestBuffer.appendField( _rxTradeDate );
      requestBuffer.appendField( _rxGrossNet );
      requestBuffer.appendField( _rxRedemOrder );
      requestBuffer.appendField( _rxAmtType );
      requestBuffer.appendField( _rxAmount );
      requestBuffer.appendField( _rxSupressMVA );
      requestBuffer.appendField( _rxSupressAdmin );
      requestBuffer.appendField( _rxIntInvestId );
      requestBuffer.appendField( _rxInvSummId );
      requestBuffer.appendField( _rxTradeAmount );
   }

}

