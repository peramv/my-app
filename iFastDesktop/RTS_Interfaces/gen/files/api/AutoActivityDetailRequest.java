// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * FundCom Auto Activity Detail Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/AutoActivityDetail.doc">AutoActivityDetail.doc</A>.
 * 
 * @author RTS Generated
 */
public class AutoActivityDetailRequest extends IFastRequest implements Serializable
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
    * Systematic Indicator member variable.
    */
   private String _SystematicIndicator = "";
            
   /**
    * RECID of Systematic member variable.
    */
   private Integer _SystematicRid = null;
            

   /**
    * Constructs the AutoActivityDetailRequest object.
    * 
    */
   AutoActivityDetailRequest()
   {
      super ( 184 );
   }

   /**
    * Constructs the AutoActivityDetailRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AutoActivityDetailRequest( String hostEncoding )
   {
      super ( 184, hostEncoding );
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
    * Sets the Systematic Indicator field for the request.
    * 
    * @param value  Value that the Systematic Indicator will be set to.
    */
   public final void setSystematicIndicator( String value )
   {
      assertUnsent();
      _SystematicIndicator = value;
   }
	
   /**
    * Sets the RECID of Systematic field for the request.
    * 
    * @param value  Value that the RECID of Systematic will be set to.
    */
   public final void setSystematicRid( Integer value )
   {
      assertUnsent();
      _SystematicRid = value;
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
      requestBuffer.appendField( _SystematicIndicator );
      requestBuffer.appendField( _SystematicRid );
   }

}

