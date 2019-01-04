// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * ID Search Validation request.
 * For additional view information see <A HREF="../../../../viewspecs/IDSearchVal.doc">IDSearchVal.doc</A>.
 * 
 * @author RTS Generated
 */
public class IDSearchValRequest extends IFastRequest implements Serializable
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
    * Where Use member variable.
    */
   private String _WhereUse = "";
            
   /**
    * Relationship member variable.
    */
   private String _RelationShip = "";
            
   /**
    * Search ID Type member variable.
    */
   private String _SrchIdType = "";
            
   /**
    * Search ID Value member variable.
    */
   private String _SrchIdValue = "";
            
   /**
    * Entity ID member variable.
    */
   private String _EntityId = "0";
            

   /**
    * Constructs the IDSearchValRequest object.
    * 
    */
   IDSearchValRequest()
   {
      super ( 417 );
   }

   /**
    * Constructs the IDSearchValRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   IDSearchValRequest( String hostEncoding )
   {
      super ( 417, hostEncoding );
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
    * Sets the Where Use field for the request.
    * 
    * @param value  Value that the Where Use will be set to.
    */
   public final void setWhereUse( String value )
   {
      assertUnsent();
      _WhereUse = value;
   }
	
   /**
    * Sets the Relationship field for the request.
    * 
    * @param value  Value that the Relationship will be set to.
    */
   public final void setRelationShip( String value )
   {
      assertUnsent();
      _RelationShip = value;
   }
	
   /**
    * Sets the Search ID Type field for the request.
    * 
    * @param value  Value that the Search ID Type will be set to.
    */
   public final void setSrchIdType( String value )
   {
      assertUnsent();
      _SrchIdType = value;
   }
	
   /**
    * Sets the Search ID Value field for the request.
    * 
    * @param value  Value that the Search ID Value will be set to.
    */
   public final void setSrchIdValue( String value )
   {
      assertUnsent();
      _SrchIdValue = value;
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
      requestBuffer.appendField( _WhereUse );
      requestBuffer.appendField( _RelationShip );
      requestBuffer.appendField( _SrchIdType );
      requestBuffer.appendField( _SrchIdValue );
      requestBuffer.appendField( _EntityId );
   }

}

