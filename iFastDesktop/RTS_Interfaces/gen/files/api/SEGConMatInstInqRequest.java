// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * SEG Contract Maturity Instruction Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/SEGConMatInstInq.doc">SEGConMatInstInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SEGConMatInstInqRequest extends IFastRequest implements Serializable
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Contract Type member variable.
    */
   private String _ContractType = "";
            
   /**
    * Contract Type ID member variable.
    */
   private Integer _ContractTypeID = null;
            

   /**
    * Constructs the SEGConMatInstInqRequest object.
    * 
    */
   SEGConMatInstInqRequest()
   {
      super ( 430 );
   }

   /**
    * Constructs the SEGConMatInstInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SEGConMatInstInqRequest( String hostEncoding )
   {
      super ( 430, hostEncoding );
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
    * Sets the Contract Type field for the request.
    * 
    * @param value  Value that the Contract Type will be set to.
    */
   public final void setContractType( String value )
   {
      assertUnsent();
      _ContractType = value;
   }
	
   /**
    * Sets the Contract Type ID field for the request.
    * 
    * @param value  Value that the Contract Type ID will be set to.
    */
   public final void setContractTypeID( Integer value )
   {
      assertUnsent();
      _ContractTypeID = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _ContractType );
      requestBuffer.appendField( _ContractTypeID );
   }

}

