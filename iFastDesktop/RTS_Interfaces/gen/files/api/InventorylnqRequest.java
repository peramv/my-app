// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Inventory  Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/Inventorylnq.doc">Inventorylnq.doc</A>.
 * 
 * @author RTS Generated
 */
public class InventorylnqRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionID = "";
            
   /**
    * User Id member variable.
    */
   private String _User_Id = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
            
            
   /**
    * Fund member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class member variable.
    */
   private String _ClassCode = "";
            
   /**
    * AccountNum member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * ActiveOnly member variable.
    */
   private Boolean _ActiveOnly = new Boolean(false);
            
   /**
    * Sort by member variable.
    */
   private String _SortBy = "";
            
   /**
    * Sort order member variable.
    */
   private String _SortOrder = "";
            

   /**
    * Constructs the InventorylnqRequest object.
    * 
    */
   InventorylnqRequest()
   {
      super ( 287 );
   }

   /**
    * Constructs the InventorylnqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   InventorylnqRequest( String hostEncoding )
   {
      super ( 287, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
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
    * Sets the Fund field for the request.
    * 
    * @param value  Value that the Fund will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class field for the request.
    * 
    * @param value  Value that the Class will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
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
    * Sets the ActiveOnly field for the request.
    * 
    * @param value  Value that the ActiveOnly will be set to.
    */
   public final void setActiveOnly( Boolean value )
   {
      assertUnsent();
      _ActiveOnly = value;
   }
	
   /**
    * Sets the Sort by field for the request.
    * 
    * @param value  Value that the Sort by will be set to.
    */
   public final void setSortBy( String value )
   {
      assertUnsent();
      _SortBy = value;
   }
	
   /**
    * Sets the Sort order field for the request.
    * 
    * @param value  Value that the Sort order will be set to.
    */
   public final void setSortOrder( String value )
   {
      assertUnsent();
      _SortOrder = value;
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
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _ActiveOnly );
      requestBuffer.appendField( _SortBy );
      requestBuffer.appendField( _SortOrder );
   }

}

