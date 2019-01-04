// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * MAT/INT/CSW Instruction List Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/InstructionListInquiry.doc">InstructionListInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class InstructionListInquiryRequest extends IFastRequest implements Serializable
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
    * SearchIntInvestId member variable.
    */
   private String _SearchIntInvestId = "0";
            

   /**
    * Constructs the InstructionListInquiryRequest object.
    * 
    */
   InstructionListInquiryRequest()
   {
      super ( 427 );
   }

   /**
    * Constructs the InstructionListInquiryRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   InstructionListInquiryRequest( String hostEncoding )
   {
      super ( 427, hostEncoding );
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
      requestBuffer.appendField( _SearchIntInvestId );
   }

}

