// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Fund Serv Broker Validation request.
 * For additional view information see <A HREF="../../../../viewspecs/FndSrvBrkVal.doc">FndSrvBrkVal.doc</A>.
 * 
 * @author RTS Generated
 */
public class FndSrvBrkValRequest extends IFastRequest implements Serializable
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
    * ValidationType member variable.
    */
   private String _ValidationType = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * NewAgencyCode member variable.
    */
   private String _NewAgencyCode = "";
            
   /**
    * NewBranch member variable.
    */
   private String _NewBranch = "";
            
   /**
    * NewAgentCode member variable.
    */
   private String _NewAgentCode = "";
            
   /**
    * AgencyCode member variable.
    */
   private String _AgencyCode = "";
            
   /**
    * Branch member variable.
    */
   private String _Branch = "";
            
   /**
    * AgentCode member variable.
    */
   private String _AgentCode = "";
            

   /**
    * Constructs the FndSrvBrkValRequest object.
    * 
    */
   FndSrvBrkValRequest()
   {
      super ( 439 );
   }

   /**
    * Constructs the FndSrvBrkValRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FndSrvBrkValRequest( String hostEncoding )
   {
      super ( 439, hostEncoding );
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
    * Sets the ValidationType field for the request.
    * 
    * @param value  Value that the ValidationType will be set to.
    */
   public final void setValidationType( String value )
   {
      assertUnsent();
      _ValidationType = value;
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
    * Sets the NewAgencyCode field for the request.
    * 
    * @param value  Value that the NewAgencyCode will be set to.
    */
   public final void setNewAgencyCode( String value )
   {
      assertUnsent();
      _NewAgencyCode = value;
   }
	
   /**
    * Sets the NewBranch field for the request.
    * 
    * @param value  Value that the NewBranch will be set to.
    */
   public final void setNewBranch( String value )
   {
      assertUnsent();
      _NewBranch = value;
   }
	
   /**
    * Sets the NewAgentCode field for the request.
    * 
    * @param value  Value that the NewAgentCode will be set to.
    */
   public final void setNewAgentCode( String value )
   {
      assertUnsent();
      _NewAgentCode = value;
   }
	
   /**
    * Sets the AgencyCode field for the request.
    * 
    * @param value  Value that the AgencyCode will be set to.
    */
   public final void setAgencyCode( String value )
   {
      assertUnsent();
      _AgencyCode = value;
   }
	
   /**
    * Sets the Branch field for the request.
    * 
    * @param value  Value that the Branch will be set to.
    */
   public final void setBranch( String value )
   {
      assertUnsent();
      _Branch = value;
   }
	
   /**
    * Sets the AgentCode field for the request.
    * 
    * @param value  Value that the AgentCode will be set to.
    */
   public final void setAgentCode( String value )
   {
      assertUnsent();
      _AgentCode = value;
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
      requestBuffer.appendField( _ValidationType );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _NewAgencyCode );
      requestBuffer.appendField( _NewBranch );
      requestBuffer.appendField( _NewAgentCode );
      requestBuffer.appendField( _AgencyCode );
      requestBuffer.appendField( _Branch );
      requestBuffer.appendField( _AgentCode );
   }

}

