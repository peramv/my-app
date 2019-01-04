// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * GIA Investment Progressive Rate List Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/GIAInvestmentProgressiveRateListInquiry.doc">GIAInvestmentProgressiveRateListInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class GIAInvestmentProgressiveRateListInquiryRequest extends IFastRequest implements Serializable
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
    * IntInvestId member variable.
    */
   private String _IntInvestId = "0";
            
   /**
    * InquiryMode member variable.
    */
   private String _InquiryMode = "";
            
   /**
    * rxAccountNum member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * rxFund member variable.
    */
   private String _Fund = "";
            
   /**
    * rxClass member variable.
    */
   private String _Class = "";
            
   /**
    * rxIntInvestType member variable.
    */
   private String _IntInvestType = "";
            
   /**
    * rxIntCalcMthd member variable.
    */
   private String _rxIntCalcMthd = "";
            
   /**
    * rxInvestTerm member variable.
    */
   private Integer _rxInvestTerm = null;
            
   /**
    * rxIntInvestDate member variable.
    */
   private Date _rxIntInvestDate = null;
            
   /**
    * rxTradeAmt member variable.
    */
   private String _rxTradeAmt = "0";
            
   /**
    * rxAddlAmt member variable.
    */
   private String _rxAddlAmt = "0";
            
   /**
    * Commission Reduction member variable.
    */
   private String _CommRedRate = "0";
            
   /**
    * IsForced member variable.
    */
   private String _IsForced = "";
            
   /**
    * ForcedRate member variable.
    */
   private String _ForcedRate = "0";
            

   /**
    * Constructs the GIAInvestmentProgressiveRateListInquiryRequest object.
    * 
    */
   GIAInvestmentProgressiveRateListInquiryRequest()
   {
      super ( 423 );
   }

   /**
    * Constructs the GIAInvestmentProgressiveRateListInquiryRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   GIAInvestmentProgressiveRateListInquiryRequest( String hostEncoding )
   {
      super ( 423, hostEncoding );
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
    * Sets the IntInvestId field for the request.
    * 
    * @param value  Value that the IntInvestId will be set to.
    */
   public final void setIntInvestId( String value )
   {
      assertUnsent();
      _IntInvestId = value;
   }
	
   /**
    * Sets the InquiryMode field for the request.
    * 
    * @param value  Value that the InquiryMode will be set to.
    */
   public final void setInquiryMode( String value )
   {
      assertUnsent();
      _InquiryMode = value;
   }
	
   /**
    * Sets the rxAccountNum field for the request.
    * 
    * @param value  Value that the rxAccountNum will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the rxFund field for the request.
    * 
    * @param value  Value that the rxFund will be set to.
    */
   public final void setFund( String value )
   {
      assertUnsent();
      _Fund = value;
   }
	
   /**
    * Sets the rxClass field for the request.
    * 
    * @param value  Value that the rxClass will be set to.
    */
   public final void setClass( String value )
   {
      assertUnsent();
      _Class = value;
   }
	
   /**
    * Sets the rxIntInvestType field for the request.
    * 
    * @param value  Value that the rxIntInvestType will be set to.
    */
   public final void setIntInvestType( String value )
   {
      assertUnsent();
      _IntInvestType = value;
   }
	
   /**
    * Sets the rxIntCalcMthd field for the request.
    * 
    * @param value  Value that the rxIntCalcMthd will be set to.
    */
   public final void setrxIntCalcMthd( String value )
   {
      assertUnsent();
      _rxIntCalcMthd = value;
   }
	
   /**
    * Sets the rxInvestTerm field for the request.
    * 
    * @param value  Value that the rxInvestTerm will be set to.
    */
   public final void setrxInvestTerm( Integer value )
   {
      assertUnsent();
      _rxInvestTerm = value;
   }
	
   /**
    * Sets the rxIntInvestDate field for the request.
    * 
    * @param value  Value that the rxIntInvestDate will be set to.
    */
   public final void setrxIntInvestDate( Date value )
   {
      assertUnsent();
      _rxIntInvestDate = value;
   }
	
   /**
    * Sets the rxTradeAmt field for the request.
    * 
    * @param value  Value that the rxTradeAmt will be set to.
    */
   public final void setrxTradeAmt( String value )
   {
      assertUnsent();
      _rxTradeAmt = value;
   }
	
   /**
    * Sets the rxAddlAmt field for the request.
    * 
    * @param value  Value that the rxAddlAmt will be set to.
    */
   public final void setrxAddlAmt( String value )
   {
      assertUnsent();
      _rxAddlAmt = value;
   }
	
   /**
    * Sets the Commission Reduction field for the request.
    * 
    * @param value  Value that the Commission Reduction will be set to.
    */
   public final void setCommRedRate( String value )
   {
      assertUnsent();
      _CommRedRate = value;
   }
	
   /**
    * Sets the IsForced field for the request.
    * 
    * @param value  Value that the IsForced will be set to.
    */
   public final void setIsForced( String value )
   {
      assertUnsent();
      _IsForced = value;
   }
	
   /**
    * Sets the ForcedRate field for the request.
    * 
    * @param value  Value that the ForcedRate will be set to.
    */
   public final void setForcedRate( String value )
   {
      assertUnsent();
      _ForcedRate = value;
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
      requestBuffer.appendField( _IntInvestId );
      requestBuffer.appendField( _InquiryMode );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _Fund );
      requestBuffer.appendField( _Class );
      requestBuffer.appendField( _IntInvestType );
      requestBuffer.appendField( _rxIntCalcMthd );
      requestBuffer.appendField( _rxInvestTerm );
      requestBuffer.appendField( _rxIntInvestDate );
      requestBuffer.appendField( _rxTradeAmt );
      requestBuffer.appendField( _rxAddlAmt );
      requestBuffer.appendField( _CommRedRate );
      requestBuffer.appendField( _IsForced );
      requestBuffer.appendField( _ForcedRate );
   }

}

