// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Dynamic Account/fund free units request.
 * For additional view information see <A HREF="../../../../viewspecs/DynAcctFreeUnits.doc">DynAcctFreeUnits.doc</A>.
 * 
 * @author RTS Generated
 */
public class DynAcctFreeUnitsRequest extends IFastRequest implements Serializable
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
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * All funds member variable.
    */
   private Boolean _AllFunds = new Boolean(false);
            
   /**
    * Fund code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class of fund member variable.
    */
   private String _ClassCode = "";
            

   /**
    * Constructs the DynAcctFreeUnitsRequest object.
    * 
    */
   DynAcctFreeUnitsRequest()
   {
      super ( 304 );
   }

   /**
    * Constructs the DynAcctFreeUnitsRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   DynAcctFreeUnitsRequest( String hostEncoding )
   {
      super ( 304, hostEncoding );
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
    * Sets the All funds field for the request.
    * 
    * @param value  Value that the All funds will be set to.
    */
   public final void setAllFunds( Boolean value )
   {
      assertUnsent();
      _AllFunds = value;
   }
	
   /**
    * Sets the Fund code field for the request.
    * 
    * @param value  Value that the Fund code will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class of fund field for the request.
    * 
    * @param value  Value that the Class of fund will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
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
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _AllFunds );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
   }

}

