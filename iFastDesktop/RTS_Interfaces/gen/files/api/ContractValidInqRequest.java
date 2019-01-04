// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Seg Fund Contract Validation Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/ContractValidInq.doc">ContractValidInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ContractValidInqRequest extends IFastRequest implements Serializable
{

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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Contract Type member variable.
    */
   private String _ContractType = "";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
            
            
            
   /**
    * Contract Type ID member variable.
    */
   private Integer _ContractTypeID = null;
            
   /**
    * EventType member variable.
    */
   private String _EventType = "";
            
   /**
    * Fund member variable.
    */
   private String _Fund = "";
            
   /**
    * Class member variable.
    */
   private String _Class = "";
            

   /**
    * Constructs the ContractValidInqRequest object.
    * 
    */
   ContractValidInqRequest()
   {
      super ( 354 );
   }

   /**
    * Constructs the ContractValidInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ContractValidInqRequest( String hostEncoding )
   {
      super ( 354, hostEncoding );
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
    * Sets the Effective Date field for the request.
    * 
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
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
    * Sets the EventType field for the request.
    * 
    * @param value  Value that the EventType will be set to.
    */
   public final void setEventType( String value )
   {
      assertUnsent();
      _EventType = value;
   }
	
   /**
    * Sets the Fund field for the request.
    * 
    * @param value  Value that the Fund will be set to.
    */
   public final void setFund( String value )
   {
      assertUnsent();
      _Fund = value;
   }
	
   /**
    * Sets the Class field for the request.
    * 
    * @param value  Value that the Class will be set to.
    */
   public final void setClass( String value )
   {
      assertUnsent();
      _Class = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _ContractType );
      requestBuffer.appendField( _EffectiveDate );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _ContractTypeID );
      requestBuffer.appendField( _EventType );
      requestBuffer.appendField( _Fund );
      requestBuffer.appendField( _Class );
   }

}

