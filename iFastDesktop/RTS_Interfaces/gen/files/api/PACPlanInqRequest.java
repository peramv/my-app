// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * PAC Plan request.
 * For additional view information see <A HREF="../../../../viewspecs/PACPlanInq.doc">PACPlanInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class PACPlanInqRequest extends IFastRequest implements Serializable
{

            
   /**
    * Session ID member variable.
    */
   private String _SessionId = "";
            
   /**
    * User ID member variable.
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
    * Plan Code member variable.
    */
   private String _PlanCode = "";
            
            
            
            

   /**
    * Constructs the PACPlanInqRequest object.
    * 
    */
   PACPlanInqRequest()
   {
      super ( 159 );
   }

   /**
    * Constructs the PACPlanInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   PACPlanInqRequest( String hostEncoding )
   {
      super ( 159, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
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
    * Sets the Plan Code field for the request.
    * 
    * @param value  Value that the Plan Code will be set to.
    */
   public final void setPlanCode( String value )
   {
      assertUnsent();
      _PlanCode = value;
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
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      requestBuffer.appendField( _PlanCode );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
   }

}

