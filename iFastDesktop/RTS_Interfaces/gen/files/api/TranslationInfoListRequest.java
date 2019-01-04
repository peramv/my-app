// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Translation Info List request.
 * For additional view information see <A HREF="../../../../viewspecs/TranslationInfoList.doc">TranslationInfoList.doc</A>.
 * 
 * @author RTS Generated
 */
public class TranslationInfoListRequest extends IFastRequest implements Serializable
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
    * Process Type member variable.
    */
   private Integer _ProcessType = null;
            
   /**
    * Translation Type member variable.
    */
   private Integer _TranslationType = null;
            
   /**
    * Lang member variable.
    */
   private String _Lang = "";
            
            
            
            

   /**
    * Constructs the TranslationInfoListRequest object.
    * 
    */
   TranslationInfoListRequest()
   {
      super ( 190 );
   }

   /**
    * Constructs the TranslationInfoListRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   TranslationInfoListRequest( String hostEncoding )
   {
      super ( 190, hostEncoding );
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
    * Sets the Process Type field for the request.
    * 
    * @param value  Value that the Process Type will be set to.
    */
   public final void setProcessType( Integer value )
   {
      assertUnsent();
      _ProcessType = value;
   }
	
   /**
    * Sets the Translation Type field for the request.
    * 
    * @param value  Value that the Translation Type will be set to.
    */
   public final void setTranslationType( Integer value )
   {
      assertUnsent();
      _TranslationType = value;
   }
	
   /**
    * Sets the Lang field for the request.
    * 
    * @param value  Value that the Lang will be set to.
    */
   public final void setLang( String value )
   {
      assertUnsent();
      _Lang = value;
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
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      requestBuffer.appendField( _ProcessType );
      requestBuffer.appendField( _TranslationType );
      requestBuffer.appendField( _Lang );
      encodeOverrideRepeatsField( requestBuffer );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
   }

}

