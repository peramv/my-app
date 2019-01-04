// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Master Seg Contract/Group Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/MstrSegContGrp.doc">MstrSegContGrp.doc</A>.
 * 
 * @author RTS Generated
 */
public class MstrSegContGrpRequest extends IFastRequest implements Serializable
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
    * Shareholder Group member variable.
    */
   private String _ShGroup = "";
            
   /**
    * Portfolio Code member variable.
    */
   private String _PortfolioCode = "";
            

   /**
    * Constructs the MstrSegContGrpRequest object.
    * 
    */
   MstrSegContGrpRequest()
   {
      super ( 133 );
   }

   /**
    * Constructs the MstrSegContGrpRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   MstrSegContGrpRequest( String hostEncoding )
   {
      super ( 133, hostEncoding );
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
    * Sets the Shareholder Group field for the request.
    * 
    * @param value  Value that the Shareholder Group will be set to.
    */
   public final void setShGroup( String value )
   {
      assertUnsent();
      _ShGroup = value;
   }
	
   /**
    * Sets the Portfolio Code field for the request.
    * 
    * @param value  Value that the Portfolio Code will be set to.
    */
   public final void setPortfolioCode( String value )
   {
      assertUnsent();
      _PortfolioCode = value;
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
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _ShGroup );
      requestBuffer.appendField( _PortfolioCode );
   }

}

