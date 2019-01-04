// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Bank List Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/BankLstInq.doc">BankLstInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class BankLstInqRequest extends IFastRequest implements Serializable
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
    * Search Type member variable.
    */
   private String _SearchType = "";
            
   /**
    * Bank Type Code member variable.
    */
   private String _BankType = "";
            
   /**
    * Bank Id Number member variable.
    */
   private String _BankIDNum = "";
            
   /**
    * Transit Code member variable.
    */
   private String _TransitCode = "";
            
   /**
    * Institution name member variable.
    */
   private String _InstName = "";
            
   /**
    * Bank Id member variable.
    */
   private Integer _BankId = null;
            
   /**
    * Institution Category member variable.
    */
   private String _InstCategory = "";
            

   /**
    * Constructs the BankLstInqRequest object.
    * 
    */
   BankLstInqRequest()
   {
      super ( 100 );
   }

   /**
    * Constructs the BankLstInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   BankLstInqRequest( String hostEncoding )
   {
      super ( 100, hostEncoding );
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
    * Sets the Search Type field for the request.
    * 
    * @param value  Value that the Search Type will be set to.
    */
   public final void setSearchType( String value )
   {
      assertUnsent();
      _SearchType = value;
   }
	
   /**
    * Sets the Bank Type Code field for the request.
    * 
    * @param value  Value that the Bank Type Code will be set to.
    */
   public final void setBankType( String value )
   {
      assertUnsent();
      _BankType = value;
   }
	
   /**
    * Sets the Bank Id Number field for the request.
    * 
    * @param value  Value that the Bank Id Number will be set to.
    */
   public final void setBankIDNum( String value )
   {
      assertUnsent();
      _BankIDNum = value;
   }
	
   /**
    * Sets the Transit Code field for the request.
    * 
    * @param value  Value that the Transit Code will be set to.
    */
   public final void setTransitCode( String value )
   {
      assertUnsent();
      _TransitCode = value;
   }
	
   /**
    * Sets the Institution name field for the request.
    * 
    * @param value  Value that the Institution name will be set to.
    */
   public final void setInstName( String value )
   {
      assertUnsent();
      _InstName = value;
   }
	
   /**
    * Sets the Bank Id field for the request.
    * 
    * @param value  Value that the Bank Id will be set to.
    */
   public final void setBankId( Integer value )
   {
      assertUnsent();
      _BankId = value;
   }
	
   /**
    * Sets the Institution Category field for the request.
    * 
    * @param value  Value that the Institution Category will be set to.
    */
   public final void setInstCategory( String value )
   {
      assertUnsent();
      _InstCategory = value;
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
      requestBuffer.appendField( _SearchType );
      requestBuffer.appendField( _BankType );
      requestBuffer.appendField( _BankIDNum );
      requestBuffer.appendField( _TransitCode );
      requestBuffer.appendField( _InstName );
      requestBuffer.appendField( _BankId );
      requestBuffer.appendField( _InstCategory );
   }

}

