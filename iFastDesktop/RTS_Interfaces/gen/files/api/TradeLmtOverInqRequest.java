// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Trade Limitation Override Enquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/TradeLmtOverInq.doc">TradeLmtOverInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class TradeLmtOverInqRequest extends IFastRequest implements Serializable
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
    * AccountNum member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * FundCode member variable.
    */
   private String _FundCode = "";
            
   /**
    * ClassCode member variable.
    */
   private String _ClassCode = "";
            
   /**
    * TransType member variable.
    */
   private String _TransType = "";
            
   /**
    * EffectiveDate member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * BrokerCode member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * BranchCode member variable.
    */
   private String _BranchCode = "";
            
   /**
    * SlsRepCode member variable.
    */
   private String _SlsRepCode = "";
            

   /**
    * Constructs the TradeLmtOverInqRequest object.
    * 
    */
   TradeLmtOverInqRequest()
   {
      super ( 462 );
   }

   /**
    * Constructs the TradeLmtOverInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   TradeLmtOverInqRequest( String hostEncoding )
   {
      super ( 462, hostEncoding );
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
    * Sets the AccountNum field for the request.
    * 
    * @param value  Value that the AccountNum will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the FundCode field for the request.
    * 
    * @param value  Value that the FundCode will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the ClassCode field for the request.
    * 
    * @param value  Value that the ClassCode will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the TransType field for the request.
    * 
    * @param value  Value that the TransType will be set to.
    */
   public final void setTransType( String value )
   {
      assertUnsent();
      _TransType = value;
   }
	
   /**
    * Sets the EffectiveDate field for the request.
    * 
    * @param value  Value that the EffectiveDate will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
   }
	
   /**
    * Sets the BrokerCode field for the request.
    * 
    * @param value  Value that the BrokerCode will be set to.
    */
   public final void setBrokerCode( String value )
   {
      assertUnsent();
      _BrokerCode = value;
   }
	
   /**
    * Sets the BranchCode field for the request.
    * 
    * @param value  Value that the BranchCode will be set to.
    */
   public final void setBranchCode( String value )
   {
      assertUnsent();
      _BranchCode = value;
   }
	
   /**
    * Sets the SlsRepCode field for the request.
    * 
    * @param value  Value that the SlsRepCode will be set to.
    */
   public final void setSlsRepCode( String value )
   {
      assertUnsent();
      _SlsRepCode = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SlsRepCode );
   }

}

