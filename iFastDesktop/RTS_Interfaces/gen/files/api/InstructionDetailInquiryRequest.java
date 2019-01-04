// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * MAT/INT/CSW Instruction Detail Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/InstructionDetailInquiry.doc">InstructionDetailInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class InstructionDetailInquiryRequest extends IFastRequest implements Serializable
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
    * SearchAcctNum member variable.
    */
   private String _SearchAcctNum = "0";
            
   /**
    * SearchInstructionType member variable.
    */
   private String _SearchInstructionType = "";
            
   /**
    * SearchFund member variable.
    */
   private String _SearchFund = "";
            
   /**
    * SearchClass member variable.
    */
   private String _SearchClass = "";
            
   /**
    * SearchTransNum member variable.
    */
   private Integer _SearchTransNum = null;
            
   /**
    * SearchEffectiveDate member variable.
    */
   private Date _SearchEffectiveDate = null;
            
   /**
    * SearchIntInvestId member variable.
    */
   private String _SearchIntInvestId = "0";
            
   /**
    * SearchGBCD member variable.
    */
   private Boolean _SearchGBCD = new Boolean(false);
            
   /**
    * SearchTransSeq member variable.
    */
   private Integer _SearchTransSeq = null;
            

   /**
    * Constructs the InstructionDetailInquiryRequest object.
    * 
    */
   InstructionDetailInquiryRequest()
   {
      super ( 428 );
   }

   /**
    * Constructs the InstructionDetailInquiryRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   InstructionDetailInquiryRequest( String hostEncoding )
   {
      super ( 428, hostEncoding );
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
    * Sets the SearchAcctNum field for the request.
    * 
    * @param value  Value that the SearchAcctNum will be set to.
    */
   public final void setSearchAcctNum( String value )
   {
      assertUnsent();
      _SearchAcctNum = value;
   }
	
   /**
    * Sets the SearchInstructionType field for the request.
    * 
    * @param value  Value that the SearchInstructionType will be set to.
    */
   public final void setSearchInstructionType( String value )
   {
      assertUnsent();
      _SearchInstructionType = value;
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
    * Sets the SearchTransNum field for the request.
    * 
    * @param value  Value that the SearchTransNum will be set to.
    */
   public final void setSearchTransNum( Integer value )
   {
      assertUnsent();
      _SearchTransNum = value;
   }
	
   /**
    * Sets the SearchEffectiveDate field for the request.
    * 
    * @param value  Value that the SearchEffectiveDate will be set to.
    */
   public final void setSearchEffectiveDate( Date value )
   {
      assertUnsent();
      _SearchEffectiveDate = value;
   }
	
   /**
    * Sets the SearchIntInvestId field for the request.
    * 
    * @param value  Value that the SearchIntInvestId will be set to.
    */
   public final void setSearchIntInvestId( String value )
   {
      assertUnsent();
      _SearchIntInvestId = value;
   }
	
   /**
    * Sets the SearchGBCD field for the request.
    * 
    * @param value  Value that the SearchGBCD will be set to.
    */
   public final void setSearchGBCD( Boolean value )
   {
      assertUnsent();
      _SearchGBCD = value;
   }
	
   /**
    * Sets the SearchTransSeq field for the request.
    * 
    * @param value  Value that the SearchTransSeq will be set to.
    */
   public final void setSearchTransSeq( Integer value )
   {
      assertUnsent();
      _SearchTransSeq = value;
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
      requestBuffer.appendField( _SearchAcctNum );
      requestBuffer.appendField( _SearchInstructionType );
      requestBuffer.appendField( _SearchFund );
      requestBuffer.appendField( _SearchClass );
      requestBuffer.appendField( _SearchTransNum );
      requestBuffer.appendField( _SearchEffectiveDate );
      requestBuffer.appendField( _SearchIntInvestId );
      requestBuffer.appendField( _SearchGBCD );
      requestBuffer.appendField( _SearchTransSeq );
   }

}

