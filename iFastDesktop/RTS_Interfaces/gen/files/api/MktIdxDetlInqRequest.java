// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Market Index Details Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/MktIdxDetlInq.doc">MktIdxDetlInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class MktIdxDetlInqRequest extends IFastRequest implements Serializable
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
    * Search Type - ALL, IndexCode or Deff member variable.
    */
   private String _SearchType = "";
            
   /**
    * Market Index Code member variable.
    */
   private String _IndexCode = "";
            
   /**
    * From Date member variable.
    */
   private Date _FromDate = null;
            
   /**
    * To Date member variable.
    */
   private Date _ToDate = null;
            

   /**
    * Constructs the MktIdxDetlInqRequest object.
    * 
    */
   MktIdxDetlInqRequest()
   {
      super ( 247 );
   }

   /**
    * Constructs the MktIdxDetlInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   MktIdxDetlInqRequest( String hostEncoding )
   {
      super ( 247, hostEncoding );
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
    * Sets the Search Type - ALL, IndexCode or Deff field for the request.
    * 
    * @param value  Value that the Search Type - ALL, IndexCode or Deff will be set to.
    */
   public final void setSearchType( String value )
   {
      assertUnsent();
      _SearchType = value;
   }
	
   /**
    * Sets the Market Index Code field for the request.
    * 
    * @param value  Value that the Market Index Code will be set to.
    */
   public final void setIndexCode( String value )
   {
      assertUnsent();
      _IndexCode = value;
   }
	
   /**
    * Sets the From Date field for the request.
    * 
    * @param value  Value that the From Date will be set to.
    */
   public final void setFromDate( Date value )
   {
      assertUnsent();
      _FromDate = value;
   }
	
   /**
    * Sets the To Date field for the request.
    * 
    * @param value  Value that the To Date will be set to.
    */
   public final void setToDate( Date value )
   {
      assertUnsent();
      _ToDate = value;
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
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SearchType );
      requestBuffer.appendField( _IndexCode );
      requestBuffer.appendField( _FromDate );
      requestBuffer.appendField( _ToDate );
   }

}

