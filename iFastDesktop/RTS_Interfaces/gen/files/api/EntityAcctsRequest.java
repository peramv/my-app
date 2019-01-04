// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Entity Associates Accounts request.
 * For additional view information see <A HREF="../../../../viewspecs/EntityAccts.doc">EntityAccts.doc</A>.
 * 
 * @author RTS Generated
 */
public class EntityAcctsRequest extends IFastRequest implements Serializable
{

   /**
    * Entity ID member variable.
    */
   private String _EntityId = "0";
            
            
   /**
    * SessionID member variable.
    */
   private String _SessionId = "";
            
   /**
    * User ID member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * CompanyID member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
            
   /**
    * Flag indicating that the purpose of the call is to find out if the record in the request already in db member variable.
    */
   private Boolean _DuplicateCheck = new Boolean(false);
            
   /**
    * recid(EntityWhereUse) member variable.
    */
   private Integer _rxEntityWhereUseRID = null;
            
   /**
    * Where Use member variable.
    */
   private String _rxWhereUse = "";
            
   /**
    * Where Use Code member variable.
    */
   private String _rxWhereUseCode = "";
            
   /**
    * Relationhip Code member variable.
    */
   private String _RelationshipCode = "";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Stop Date member variable.
    */
   private Date _StopDate = null;
            
   /**
    * Return Same CIF Accounts member variable.
    */
   private Boolean _RetSameCIFAcct = new Boolean(false);
            

   /**
    * Constructs the EntityAcctsRequest object.
    * 
    */
   EntityAcctsRequest()
   {
      super ( 61 );
   }

   /**
    * Constructs the EntityAcctsRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   EntityAcctsRequest( String hostEncoding )
   {
      super ( 61, hostEncoding );
   }

   /**
    * Sets the Entity ID field for the request.
    * 
    * @param value  Value that the Entity ID will be set to.
    */
   public final void setEntityId( String value )
   {
      assertUnsent();
      _EntityId = value;
   }
	
   /**
    * Sets the SessionID field for the request.
    * 
    * @param value  Value that the SessionID will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
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
    * Sets the CompanyID field for the request.
    * 
    * @param value  Value that the CompanyID will be set to.
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
    * Sets the Flag indicating that the purpose of the call is to find out if the record in the request already in db field for the request.
    * 
    * @param value  Value that the Flag indicating that the purpose of the call is to find out if the record in the request already in db will be set to.
    */
   public final void setDuplicateCheck( Boolean value )
   {
      assertUnsent();
      _DuplicateCheck = value;
   }
	
   /**
    * Sets the recid(EntityWhereUse) field for the request.
    * 
    * @param value  Value that the recid(EntityWhereUse) will be set to.
    */
   public final void setrxEntityWhereUseRID( Integer value )
   {
      assertUnsent();
      _rxEntityWhereUseRID = value;
   }
	
   /**
    * Sets the Where Use field for the request.
    * 
    * @param value  Value that the Where Use will be set to.
    */
   public final void setrxWhereUse( String value )
   {
      assertUnsent();
      _rxWhereUse = value;
   }
	
   /**
    * Sets the Where Use Code field for the request.
    * 
    * @param value  Value that the Where Use Code will be set to.
    */
   public final void setrxWhereUseCode( String value )
   {
      assertUnsent();
      _rxWhereUseCode = value;
   }
	
   /**
    * Sets the Relationhip Code field for the request.
    * 
    * @param value  Value that the Relationhip Code will be set to.
    */
   public final void setRelationshipCode( String value )
   {
      assertUnsent();
      _RelationshipCode = value;
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
    * Sets the Stop Date field for the request.
    * 
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( Date value )
   {
      assertUnsent();
      _StopDate = value;
   }
	
   /**
    * Sets the Return Same CIF Accounts field for the request.
    * 
    * @param value  Value that the Return Same CIF Accounts will be set to.
    */
   public final void setRetSameCIFAcct( Boolean value )
   {
      assertUnsent();
      _RetSameCIFAcct = value;
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
      requestBuffer.appendField( _EntityId );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _DuplicateCheck );
      requestBuffer.appendField( _rxEntityWhereUseRID );
      requestBuffer.appendField( _rxWhereUse );
      requestBuffer.appendField( _rxWhereUseCode );
      requestBuffer.appendField( _RelationshipCode );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _StopDate );
      requestBuffer.appendField( _RetSameCIFAcct );
   }

}

